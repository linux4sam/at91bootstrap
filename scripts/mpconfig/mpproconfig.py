# SPDX-License-Identifier: MIT
# /*
#  * Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries
#  *
#  * Author: Arokkia Jerald Praveen <Praveendevadas.Arokkiajerald@microchip.com>
#  *
#  * Proconfig is used to create and update MPPRO Kconfig UI
#  * Proconfig consumes NodeType and TreeNodeData class for creating MPPRO Kconfig UI
#  */

from kconfiglib import Symbol, Kconfig, expr_value, Choice
from knodeinfo import getNodeInfoString, setKConfig, getNodeName
import json
import uuid

(
    _T_ALLNOCONFIG_Y,
    _T_AND,
    _T_BOOL,
    _T_CHOICE,
    _T_CLOSE_PAREN,
    _T_COMMENT,
    _T_CONFIG,
    _T_DEFAULT,
    _T_DEFCONFIG_LIST,
    _T_DEF_BOOL,
    _T_DEF_HEX,
    _T_DEF_INT,
    _T_DEF_STRING,
    _T_DEF_TRISTATE,
    _T_DEPENDS,
    _T_ENDCHOICE,
    _T_ENDIF,
    _T_ENDMENU,
    _T_ENV,
    _T_EQUAL,
    _T_GREATER,
    _T_GREATER_EQUAL,
    _T_HELP,
    _T_HEX,
    _T_IF,
    _T_IMPLY,
    _T_INT,
    _T_LESS,
    _T_LESS_EQUAL,
    _T_MAINMENU,
    _T_MENU,
    _T_MENUCONFIG,
    _T_MODULES,
    _T_NOT,
    _T_ON,
    _T_OPEN_PAREN,
    _T_OPTION,
    _T_OPTIONAL,
    _T_OR,
    _T_ORSOURCE,
    _T_OSOURCE,
    _T_PROMPT,
    _T_RANGE,
    _T_RSOURCE,
    _T_SELECT,
    _T_SOURCE,
    _T_STRING,
    _T_TRISTATE,
    _T_UNEQUAL,
    _T_VISIBLE,
) = range(1, 51)

# Node types
MENU = _T_MENU
COMMENT = _T_COMMENT

# Expression types
AND = _T_AND
OR = _T_OR
NOT = _T_NOT
EQUAL = _T_EQUAL
UNEQUAL = _T_UNEQUAL
LESS = _T_LESS
LESS_EQUAL = _T_LESS_EQUAL
GREATER = _T_GREATER
GREATER_EQUAL = _T_GREATER_EQUAL

UNKNOWN = 0
BOOL = _T_BOOL
TRISTATE = _T_TRISTATE
STRING = _T_STRING
INT = _T_INT
HEX = _T_HEX


class NodeType():
    """Used to determine what GUI control to use in the visual tree."""
    _unknown = 0
    _radio = 1
    _bool = 2
    _tri = 3
    _text = 4
    _menu = 5
    _comment = 6

    nodeType = _unknown

    def __init__(self, t):
        self.nodeType = t

    def isType(self, t_list):
        return self.nodeType in t_list

    def getType(self):
        return self.nodeType


class TreeNodeData(object):
    """These are the data objects that goes into the tree data model."""

    def __init__(self, node, tree):
        """Create a TreeNodeData object

        Parameters
        ----------
            node : Kconfig.MenuNode
                The Kconfiglib node object that this tree node visualizes.
            tree : KConfigTree
                The tree this node object belongs to. Needed for sending events to the tree.
        """
        self.knode = node
        self.tree = tree
        self.expanded = False

    def getNodeType(self):
        """Returns the node type"""
        item = self.knode.item

        if item == MENU:
            return NodeType(NodeType._menu)

        if item == COMMENT:
            return NodeType(NodeType._comment)

        if not hasattr(item, 'orig_type'):
            return NodeType(NodeType._unknown)

        if item.orig_type in (STRING, INT, HEX):
            return NodeType(NodeType._text)

        # BOOL or TRISTATE
        if isinstance(item, Symbol) and item.choice:
            # Choice symbol in y-mode choice
            return NodeType(NodeType._radio)

        if len(item.assignable) <= 1:
            # Pinned to a single value
            if isinstance(item, Choice):
                return NodeType(NodeType._menu)

        if item.type == BOOL:
            return NodeType(NodeType._bool)

        if item.assignable == (1, 2):
            return NodeType(NodeType._tri)

        return NodeType(NodeType._tri)

    def getText(self):
        """Return the text to display on the tree node"""
        if self.knode and hasattr(self.knode, 'prompt') and self.knode.prompt:
            return self.knode.prompt[0]
        return getNodeName(self.knode).strip()

    def getValue(self):
        """Returns a string-type value, used for STRING, INT, HEX node types."""
        if self.knode.item == MENU or self.knode.item == COMMENT:
            return None

        return self.knode.item.str_value

    def getTriValue(self):
        """Returns a boolean or tristate value. A bool checkbox has the values 0 and 2,
        while a tristate has 0, 1 and 2. 0 = False/N, 1 = Module/M, 2 = True/Y"""
        if self.knode.item == MENU or self.knode.item == COMMENT:
            return None

        # log.info(self.getText(), str(self.knode.item.tri_value)))
        return self.knode.item.tri_value

    def setValue(self, val):
        """Set a string value. Can be a text string, or an integer (or hex) encoded as a string."""
        # log.info("TreeNodeData.setValue " + self.getText() + " " + str(val) + " was " + self.getValue())
        self.knode.item.set_value(val)

    def setTriValue(self, n):
        """Set a tristate or bool value. 0 = False/N, 1 = Module/M, 2 = True/Y"""
        # log.info("TreeNodeData.setTriValue", self.getText(), n)
        self.knode.item.set_value(n)

    def getVisible(self):
        """Return the visibility state of the node."""
        return TreeNodeData.isVisible(self.knode)

    @staticmethod
    def isVisible(node):
        """Return the visibility state of the node passed as an argument."""
        return node.prompt and expr_value(node.prompt[1]) and not \
            (node.item == MENU and not expr_value(node.visibility))


class ProConfig():

    def __init__(self, path):
        self.kconfig = Kconfig(path)
        self.proxyArray = []
        self.shadowModel = None
        setKConfig(self.kconfig)

    def getkconfig(self):
        return self.kconfig

    def getproxyarray(self):
        return self.proxyArray

    def createKconfShadowModel(self):
        rootNode = {}
        rootNode['id'] = str(uuid.uuid4())
        rootNode['label'] = self.kconfig.mainmenu_text
        rootNode['children'] = []
        self.addNodes(rootNode, self.kconfig.top_node.list)
        self.shadowModel = rootNode
        return json.dumps(self.shadowModel)

    def addNodes(self, parent, node):
        while node:
            treeNodeData = TreeNodeData(node, self)
            uniqueid = str(uuid.uuid4())
            newUiNode = self.uiNodeFormation(treeNodeData, uniqueid)
            self.proxyArrayUpdate(treeNodeData, uniqueid, newUiNode)
            parent['children'].append(newUiNode)

            if node.list:
                self.addNodes(newUiNode, node.list)

            node = node.next

    def uiNodeFormation(self, treeNodeData, uniqueid):
        nodeObject = {}
        nodeObject['id'] = uniqueid
        nodeObject['label'] = treeNodeData.getText()
        nodeObject['value'] = treeNodeData.getValue()
        nodeObject['help'] = getNodeInfoString(treeNodeData.knode)
        nodetype = treeNodeData.getNodeType().getType()
        nodeObject['type'] = self.switch(nodetype)
        visiblity = treeNodeData.getVisible()
        nodeObject['isVisible'] = False if visiblity == 0 or visiblity is None else True
        nodeObject['children'] = []
        return nodeObject

    def proxyArrayUpdate(self, treenodedata, uniqueid, newUiNode):
        proxyObject = {}
        proxyObject['id'] = uniqueid
        proxyObject['treenodedata'] = treenodedata
        proxyObject['uinode'] = newUiNode
        self.proxyArray.append(proxyObject)

    def proxyObjectLooping(self, uniqueid):
        found = next((element for element in self.proxyArray if element["id"] == uniqueid), None)
        return found

    def switch(self, nodetype):
        if nodetype == 0:
            return "string"
        elif nodetype == 1:
            return "choice"
        elif nodetype == 2:
            return "bool"
        elif nodetype == 3:
            return "bool"
        elif nodetype == 4:
            return "withedit"
        elif nodetype == 5:
            return "string"
        elif nodetype == 6:
            return "comment"
        else:
            return "string"

    def createUpdatedModel(self, uniqueid, val):
        obj = self.proxyObjectLooping(uniqueid)
        treenodedata = obj["treenodedata"]
        treenodedata.setValue(val)
        rootNode = {}
        rootNode['id'] = self.shadowModel['id']
        rootNode['label'] = self.kconfig.mainmenu_text
        rootNode['children'] = []
        self.addVisibleNodes(rootNode, self.shadowModel)
        return json.dumps(rootNode)

    def addVisibleNodes(self, visibleParent, shadowParent):
        shadowChildren = shadowParent['children']
        for x in shadowChildren:
            shadowChild = x
            proxyObject = self.proxyObjectLooping(shadowChild['id'])
            visibleChild = self.updateTreeNode(proxyObject)
            visibleParent['children'].append(visibleChild)

            if len(shadowChild['children']) > 0:
                self.addVisibleNodes(visibleChild, shadowChild)
        return visibleParent

    def updateTreeNode(self, proxyObject):
        uinodedata = proxyObject['uinode']
        treenodedata = proxyObject['treenodedata']
        visiblity = treenodedata.getVisible()
        visible = False if visiblity == 0 or visiblity is None else True
        updateduinode = {**uinodedata, 'value': treenodedata.getValue(), 'isVisible': visible, 'children': []}
        return updateduinode