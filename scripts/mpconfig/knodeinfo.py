from kconfiglib import Kconfig, MenuNode, Symbol, Choice, expr_str, expr_value, split_expr, standard_sc_expr_str, TRI_TO_STR, AND, OR

def setKConfig(kconfig):
    global _kconfig
    _kconfig = kconfig

def getNodeName(node):
    if isinstance(node.item, Symbol) or isinstance(node.item, Choice):
        return _name_info(node.item)

    return _kconfig_def_info(node)

def getNodeInfoString(node):
    # Returns information about the menu node 'node' as a string.
    #
    # The helper functions are responsible for adding newlines. This allows
    # them to return "" if they don't want to add any output.

    if isinstance(node.item, Symbol):
        sym = node.item

        return (
            _name_info(sym) +
            _help_info(sym) +
            _direct_dep_info(sym) +
            _defaults_info(sym) +
            _select_imply_info(sym) +
            _kconfig_def_info(sym)
        )

    if isinstance(node.item, Choice):
        choice = node.item

        return (
            _name_info(choice) +
            _help_info(choice) +
            'Mode: {}\n\n'.format(choice.str_value) +
            _choice_syms_info(choice) +
            _direct_dep_info(choice) +
            _defaults_info(choice) +
            _kconfig_def_info(choice)
        )

    # node.item in (MENU, COMMENT)
    return _kconfig_def_info(node)


    return "Text here"


def _name_info(sc):
    # Returns a string with the name of the symbol/choice. Choices are shown as
    # <choice (name if any)>.

    return (sc.name if sc.name else standard_sc_expr_str(sc)) + "\n\n"


def _value_info(sym):
    # Returns a string showing 'sym's value

    # Only put quotes around the value for string symbols
    return "Value: {}\n".format(
        '"{}"'.format(sym.str_value)
        if sym.orig_type == STRING
        else sym.str_value)


def _choice_syms_info(choice):
    # Returns a string listing the choice symbols in 'choice'. Adds
    # "(selected)" next to the selected one.

    s = "Choice symbols:\n"

    for sym in choice.syms:
        s += "  - " + sym.name
        if sym is choice.selection:
            s += " (selected)"
        s += "\n"

    return s + "\n"


def _help_info(sc):
    # Returns a string with the help text(s) of 'sc' (Symbol or Choice).
    # Symbols and choices defined in multiple locations can have multiple help
    # texts.

    s = ""

    for node in sc.nodes:
        if node.help is not None:
            s += node.help + "\n\n"

    return s


def _direct_dep_info(sc):
    # Returns a string describing the direct dependencies of 'sc' (Symbol or
    # Choice). The direct dependencies are the OR of the dependencies from each
    # definition location. The dependencies at each definition location come
    # from 'depends on' and dependencies inherited from parent items.

    return "" if sc.direct_dep is _kconfig.y else \
        'Direct dependencies (={}):\n{}\n' \
        .format(TRI_TO_STR[expr_value(sc.direct_dep)],
                _split_expr_info(sc.direct_dep, 2))


def _defaults_info(sc):
    # Returns a string describing the defaults of 'sc' (Symbol or Choice)

    if not sc.defaults:
        return ""

    s = "Default"
    if len(sc.defaults) > 1:
        s += "s"
    s += ":\n"

    for val, cond in sc.orig_defaults:
        s += "  - "
        if isinstance(sc, Symbol):
            s += _expr_str(val)

            # Skip the tristate value hint if the expression is just a single
            # symbol. _expr_str() already shows its value as a string.
            #
            # This also avoids showing the tristate value for string/int/hex
            # defaults, which wouldn't make any sense.
            if isinstance(val, tuple):
                s += '  (={})'.format(TRI_TO_STR[expr_value(val)])
        else:
            # Don't print the value next to the symbol name for choice
            # defaults, as it looks a bit confusing
            s += val.name
        s += "\n"

        if cond is not _kconfig.y:
            s += "    Condition (={}):\n{}" \
                .format(TRI_TO_STR[expr_value(cond)],
                        _split_expr_info(cond, 4))

    return s + "\n"

def _split_expr_info(expr, indent):
    # Returns a string with 'expr' split into its top-level && or || operands,
    # with one operand per line, together with the operand's value. This is
    # usually enough to get something readable for long expressions. A fancier
    # recursive thingy would be possible too.
    #
    # indent:
    #   Number of leading spaces to add before the split expression.

    if len(split_expr(expr, AND)) > 1:
        split_op = AND
        op_str = "&&"
    else:
        split_op = OR
        op_str = "||"

    s = ""
    for i, term in enumerate(split_expr(expr, split_op)):
        s += "{}{} {}".format(indent*" ",
                            "  " if i == 0 else op_str,
                            _expr_str(term))

        # Don't bother showing the value hint if the expression is just a
        # single symbol. _expr_str() already shows its value.
        if isinstance(term, tuple):
            s += "  (={})".format(TRI_TO_STR[expr_value(term)])

        s += "\n"

    return s


def _select_imply_info(sym):
    # Returns a string with information about which symbols 'select' or 'imply'
    # 'sym'. The selecting/implying symbols are grouped according to which
    # value they select/imply 'sym' to (n/m/y).

    def sis(expr, val, title):
        # sis = selects/implies
        sis = [si for si in split_expr(expr, OR) if expr_value(si) == val]
        if not sis:
            return ""

        res = title
        for si in sis:
            res += "  - {}\n".format(split_expr(si, AND)[0].name)
        return res + "\n"

    s = ""

    if sym.rev_dep is not _kconfig.n:
        s += sis(sym.rev_dep, 2,
                "Symbols currently y-selecting this symbol:\n")
        s += sis(sym.rev_dep, 1,
                "Symbols currently m-selecting this symbol:\n")
        s += sis(sym.rev_dep, 0,
                "Symbols currently n-selecting this symbol (no effect):\n")

    if sym.weak_rev_dep is not _kconfig.n:
        s += sis(sym.weak_rev_dep, 2,
                "Symbols currently y-implying this symbol:\n")
        s += sis(sym.weak_rev_dep, 1,
                "Symbols currently m-implying this symbol:\n")
        s += sis(sym.weak_rev_dep, 0,
                "Symbols currently n-implying this symbol (no effect):\n")

    return s


def _kconfig_def_info(item):
    # Returns a string with the definition of 'item' in Kconfig syntax,
    # together with the definition location(s) and their include and menu paths

    nodes = [item] if isinstance(item, MenuNode) else item.nodes

    s = "Kconfig definition{}, with parent deps. propagated to 'depends on'\n" \
        .format("s" if len(nodes) > 1 else "")
    s += (len(s) - 1)*"="

    for node in nodes:
        s += "\n\n" \
            "At {}:{}\n" \
            "{}" \
            "Menu path: {}\n\n" \
            "{}" \
            .format(node.filename, node.linenr,
                    _include_path_info(node),
                    _menu_path_info(node),
                    node.custom_str(_name_and_val_str))

    return s


def _include_path_info(node):
    if not node.include_path:
        # In the top-level Kconfig file
        return ""

    return "Included via {}\n".format(
        " -> ".join("{}:{}".format(filename, linenr)
                    for filename, linenr in node.include_path))


def _menu_path_info(node):
    # Returns a string describing the menu path leading up to 'node'

    path = ""

    while node.parent is not _kconfig.top_node:
        node = node.parent

        # Promptless choices might appear among the parents. Use
        # standard_sc_expr_str() for them, so that they show up as
        # '<choice (name if any)>'.
        path = " -> " + (node.prompt[0] if node.prompt else
                        standard_sc_expr_str(node.item)) + path

    return "(Top)" + path

def _name_and_val_str(sc):
    # Custom symbol/choice printer that shows symbol values after symbols

    # Show the values of non-constant (non-quoted) symbols that don't look like
    # numbers. Things like 123 are actually symbol references, and only work as
    # expected due to undefined symbols getting their name as their value.
    # Showing the symbol value for those isn't helpful though.
    if isinstance(sc, Symbol) and not sc.is_constant and not _is_num(sc.name):
        if not sc.nodes:
            # Undefined symbol reference
            return "{}(undefined/n)".format(sc.name)

        return '{}(={})'.format(sc.name, sc.str_value)

    # For other items, use the standard format
    return standard_sc_expr_str(sc)


def _expr_str(expr):
    # Custom expression printer that shows symbol values
    return expr_str(expr, _name_and_val_str)


def _is_num(name):
    # Heuristic to see if a symbol name looks like a number, for nicer output
    # when printing expressions. Things like 16 are actually symbol names, only
    # they get their name as their value when the symbol is undefined.

    try:
        int(name)
    except ValueError:
        if not name.startswith(("0x", "0X")):
            return False

        try:
            int(name, 16)
        except ValueError:
            return False

    return True
