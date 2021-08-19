import os
import sys
import base64
import fnmatch
from kconfiglib import Kconfig, expr_value, Symbol, Choice, MENU, COMMENT, BOOL, STRING, INT, HEX
from java.awt import BorderLayout, Dimension, FlowLayout
from java.awt.event import ActionListener, MouseEvent
from javax.swing import BorderFactory, BoxLayout, ImageIcon, JButton, JCheckBox, JFileChooser, JFrame, JLabel, JPanel, JRadioButton, JScrollPane, JSplitPane, JTextArea, JTextField, JTree
from javax.swing.event import ChangeEvent, DocumentListener, TreeExpansionListener, TreeSelectionListener, CellEditorListener
from javax.swing.tree import DefaultTreeModel, DefaultMutableTreeNode, DefaultTreeCellRenderer, TreeCellEditor, TreePath
from events import addActionListener
# For icons in code
from org.python.core.util import StringUtil

if 'knodeinfo' in sys.modules:
   del sys.modules["knodeinfo"]
from knodeinfo import getNodeInfoString, getNodeName, setKConfig


class PrintLogger():
    def info(self, log_string):
        print(log_string)

log = PrintLogger()

# If True, use GIF image data embedded in this file instead of separate GIF
# files. See _load_images().
_USE_EMBEDDED_IMAGES = True

def _load_images():
    # Loads GIF images, creating the global _*_img ImageIcon variables.
    # Base64-encoded images embedded in this script are used if
    # _USE_EMBEDDED_IMAGES is True, and separate image files in the same
    # directory as the script otherwise.
    #
    # Using a global variable indirectly prevents the image from being
    # garbage-collected. Passing an image to a Tkinter function isn't enough to
    # keep it alive.

    def load_image(name, data):
        var_name = "_{}_img".format(name)

        if _USE_EMBEDDED_IMAGES:
            globals()[var_name] = ImageIcon(StringUtil.toBytes(base64.b64decode(data)))
        else:
            globals()[var_name] = ImageIcon(
                file=os.path.join(os.path.dirname(__file__), name + ".gif"))

    # Note: Base64 data can be put on the clipboard with
    #   $ base64 -w0 foo.gif | xclip

    load_image("icon", "R0lGODlhMAAwAPEDAAAAAADQAO7u7v///yH5BAUKAAMALAAAAAAwADAAAAL/nI+gy+2Pokyv2jazuZxryQjiSJZmyXxHeLbumH6sEATvW8OLNtf5bfLZRLFITzgEipDJ4mYxYv6A0ubuqYhWk66tVTE4enHer7jcKvt0LLUw6P45lvEprT6c0+v7OBuqhYdHohcoqIbSAHc4ljhDwrh1UlgSydRCWWlp5wiYZvmSuSh4IzrqV6p4cwhkCsmY+nhK6uJ6t1mrOhuJqfu6+WYiCiwl7HtLjNSZZZis/MeM7NY3TaRKS40ooDeoiVqIultsrav92bi9c3a5KkkOsOJZpSS99m4k/0zPng4Gks9JSbB+8DIcoQfnjwpZCHv5W+ip4aQrKrB0uOikYhiMCBw1/uPoQUMBADs=")
    load_image("n_bool", "R0lGODdhEAAQAPAAAAgICP///ywAAAAAEAAQAAACIISPacHtvp5kcb5qG85hZ2+BkyiRF8BBaEqtrKkqslEAADs=")
    load_image("y_bool", "R0lGODdhEAAQAPEAAAgICADQAP///wAAACwAAAAAEAAQAAACMoSPacLtvlh4YrIYsst2cV19AvaVF9CUXBNJJoum7ymrsKuCnhiupIWjSSjAFuWhSCIKADs=")
    load_image("n_tri", "R0lGODlhEAAQAPD/AAEBAf///yH5BAUKAAIALAAAAAAQABAAAAInlI+pBrAKQnCPSUlXvFhznlkfeGwjKZhnJ65h6nrfi6h0st2QXikFADs=")
    load_image("m_tri", "R0lGODlhEAAQAPEDAAEBAeQMuv///wAAACH5BAUKAAMALAAAAAAQABAAAAI5nI+pBrAWAhPCjYhiAJQCnWmdoElHGVBoiK5M21ofXFpXRIrgiecqxkuNciZIhNOZFRNI24PhfEoLADs=")
    load_image("y_tri", "R0lGODlhEAAQAPEDAAICAgDQAP///wAAACH5BAUKAAMALAAAAAAQABAAAAI0nI+pBrAYBhDCRRUypfmergmgZ4xjMpmaw2zmxk7cCB+pWiVqp4MzDwn9FhGZ5WFjIZeGAgA7")
    load_image("m_my", "R0lGODlhEAAQAPEDAAAAAOQMuv///wAAACH5BAUKAAMALAAAAAAQABAAAAI5nIGpxiAPI2ghxFinq/ZygQhc94zgZopmOLYf67anGr+oZdp02emfV5n9MEHN5QhqICETxkABbQ4KADs=")
    load_image("y_my", "R0lGODlhEAAQAPH/AAAAAADQAAPRA////yH5BAUKAAQALAAAAAAQABAAAAM+SArcrhCMSSuIM9Q8rxxBWIXawIBkmWonupLd565Um9G1PIs59fKmzw8WnAlusBYR2SEIN6DmAmqBLBxYSAIAOw==")
    load_image("n_locked", "R0lGODlhEAAQAPABAAAAAP///yH5BAUKAAEALAAAAAAQABAAAAIgjB8AyKwN04pu0vMutpqqz4Hih4ydlnUpyl2r23pxUAAAOw==")
    load_image("m_locked", "R0lGODlhEAAQAPD/AAAAAOQMuiH5BAUKAAIALAAAAAAQABAAAAIylC8AyKwN04ohnGcqqlZmfXDWI26iInZoyiore05walolV39ftxsYHgL9QBBMBGFEFAAAOw==")
    load_image("y_locked", "R0lGODlhEAAQAPD/AAAAAADQACH5BAUKAAIALAAAAAAQABAAAAIylC8AyKzNgnlCtoDTwvZwrHydIYpQmR3KWq4uK74IOnp0HQPmnD3cOVlUIAgKsShkFAAAOw==")
    load_image("not_selected", "R0lGODlhEAAQAPD/AAAAAP///yH5BAUKAAIALAAAAAAQABAAAAIrlA2px6IBw2IpWglOvTYhzmUbGD3kNZ5QqrKn2YrqigCxZoMelU6No9gdCgA7")
    load_image("selected", "R0lGODlhEAAQAPD/AAAAAP///yH5BAUKAAIALAAAAAAQABAAAAIzlA2px6IBw2IpWglOvTah/kTZhimASJomiqonlLov1qptHTsgKSEzh9H8QI0QzNPwmRoFADs=")
    load_image("edit", "R0lGODlhEAAQAPIFAAAAAKOLAMuuEPvXCvrxvgAAAAAAAAAAACH5BAUKAAUALAAAAAAQABAAAANCWLqw/gqMBp8cszJxcwVC2FEOEIAi5kVBi3IqWZhuCGMyfdpj2e4pnK+WAshmvxeAcETWlsxPkkBtsqBMa8TIBSQAADs=")


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
    def __init__ (self, node, tree):
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

        if not item.orig_type:
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
        if self.knode and self.knode.prompt:
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
        self.tree.updateTree()

    def setTriValue(self, n):
        """Set a tristate or bool value. 0 = False/N, 1 = Module/M, 2 = True/Y"""
        # log.info("TreeNodeData.setTriValue", self.getText(), n)
        self.knode.item.set_value(n)
        self.tree.updateTree()

    def getVisible(self):
        """Return the visibility state of the node."""
        return TreeNodeData.isVisible(self.knode)

    @staticmethod
    def isVisible(node):
        """Return the visibility state of the node passed as an argument."""
        return node.prompt and expr_value(node.prompt[1]) and not \
            (node.item == MENU and not expr_value(node.visibility))

    def isExpanded(self):
        return self.expanded

    def setExpanded(self, expanded):
        self.expanded = expanded

    def search(self, searchString, invisibleMatch):
        """Search all text related to this node for searchString.
        If it matches, it will tag the node as a search match.
        If invisibleMatch = False and the node is not visible, the search match will be False.
        The search match result (bool) is returned."""
        if self.getVisible() > 0 or invisibleMatch:
            infoText = self.getText()
            searchString = "*" + searchString + "*"
            self.searchMatch = fnmatch.fnmatch(infoText.lower(), searchString.lower())
        else:
            self.searchMatch = False

        return self.searchMatch

    def setSearchMatch(self, match):
        """Tags the node with a search match"""
        self.searchMatch = match

    def isSearchMatch(self):
        return self.searchMatch

    def toString(self):
        return self.getText() + " = " + str(self.getValue())


class TristateCheckBox(JCheckBox):
    """Custom tristate checkbox implementation."""
    serialVersionUID = 1
    triState = 0
    _load_images()
    selected = _y_tri_img
    unselected = _n_tri_img
    halfselected = _m_tri_img

    def __init__(self, eventHandler = None):
        """Creates a TristateCheckBox object

        Arguments
        ---------
            eventHandler : ActionListener
                If supplied, the event handler will be called when
                the tristate checkbox state changes.
        """
        JCheckBox.__init__(self)

        if eventHandler:
            addActionListener(self, eventHandler)

        addActionListener(self, self.actionPerformed)

    def paint(self, g):
        """Called when the tree needs to paint the checkbox icon."""
        if self.triState == 2:
            self.setIcon(self.selected)
        elif self.triState == 1:
            self.setIcon(self.halfselected)
        else:
            self.setIcon(self.unselected)

        JCheckBox.paint(self, g)

    def getTriState(self):
        """Return the tristate value (0, 1 or 2)."""
        return self.triState

    def setTriState(self, tri):
        """Set tristate value (0, 1 or 2)."""
        self.triState = tri

    def actionPerformed(self, e):
        """Increments the checkbox value when clicked"""
        # log.info("actionPerformed()")
        tcb = e.getSource()
        newVal = (tcb.getTriState() + 1) % 3
        tcb.setTriState(newVal)


class CustomCellRenderer(DefaultTreeCellRenderer):
    """Renders the various tree controls (checkbox, tristate checkbox, string values etc.)"""
    def __init__(self):
        DefaultTreeCellRenderer.__init__(self)

        flowLayout = FlowLayout(FlowLayout.LEFT, 0, 0)

        self.cbPanel = JPanel(flowLayout)
        self.cb = JCheckBox()
        self.cb.setBackground(None)
        self.cbPanel.add(self.cb)
        self.cbLabel = JLabel()
        self.cbPanel.add(self.cbLabel)

        self.tcbPanel = JPanel(flowLayout)
        self.tcb = TristateCheckBox()
        self.tcb.setBackground(None)
        self.tcbPanel.add(self.tcb)
        self.tcbLabel = JLabel()
        self.tcbPanel.add(self.tcbLabel)

        self.rbPanel = JPanel(flowLayout)
        self.rb = JRadioButton()
        self.rb.setBackground(None)
        self.rbPanel.add(self.rb)
        self.rbLabel = JLabel()
        self.rbPanel.add(self.rbLabel)

    def getTreeCellRendererComponent(self, tree, value, selected, expanded, leaf, row, hasFocus):
        """Return a swing control appropriate for the node type of the supplied value"""
        if isinstance(value, DefaultMutableTreeNode):
            nodeData = value.getUserObject()
            if isinstance(nodeData, TreeNodeData):
                t = nodeData.getNodeType()

                isEnabled = nodeData.getVisible() > 0

                # Boolean checkbox
                if t.isType([NodeType._bool]):
                    self.cbLabel.setText(nodeData.getText())
                    self.cb.setEnabled(isEnabled)
                    self.cbLabel.setEnabled(isEnabled)
                    if nodeData.getTriValue() == 0:
                        self.cb.setSelected(False)
                    else:
                        self.cb.setSelected(True)
                    control = self.cbPanel

                # Tristate chekcbox
                elif t.isType([NodeType._tri]):
                    control = self.tcbPanel
                    self.tcbLabel.setText(nodeData.getText())
                    self.tcb.setEnabled(isEnabled)
                    self.tcbLabel.setEnabled(isEnabled)
                    self.tcb.setTriState(nodeData.getTriValue())

                # Radio button
                elif t.isType([NodeType._radio]):
                    self.rbLabel.setText(nodeData.getText())
                    self.rb.setEnabled(isEnabled)
                    self.rbLabel.setEnabled(isEnabled)
                    if nodeData.getTriValue() == 0:
                        self.rb.setSelected(False)
                    else:
                        self.rb.setSelected(True)
                    control = self.rbPanel

                # Text field
                elif t.isType([NodeType._text]):
                    control = DefaultTreeCellRenderer.getTreeCellRendererComponent(self, tree, value, selected, expanded, leaf, row, hasFocus)
                    control.setText(nodeData.getText() + ": " + str(nodeData.getValue()))

                # Default tree cell (a node with an icon and a label)
                else:
                    control = DefaultTreeCellRenderer.getTreeCellRendererComponent(self, tree, value, selected, expanded, leaf, row, hasFocus)
                    control.setText(nodeData.getText())

                self.setColors(control, nodeData, selected)   # Background color for the tree item

                # log.info("getTreeCellRendererComponent", t.getType(), isEnabled, "'" + nodeData.getText() + "'")

                control.setEnabled(isEnabled)
                return control

        # log.info("Warning: getTreeCellRendererComponent() fallthrough", nodeData)
        return DefaultTreeCellRenderer.getTreeCellRendererComponent(self, tree, value, selected, expanded, leaf, row, hasFocus)

    def setColors(self, control, data, selected):
        """Set background color fot the tree item."""
        if selected:
            control.setForeground(self.getTextSelectionColor())
            control.setBackground(self.getBackgroundSelectionColor())
        else:
            control.setForeground(self.getTextNonSelectionColor())
            control.setBackground(self.getBackgroundNonSelectionColor())


class CustomCellEditor(TreeCellEditor, ActionListener):
    """Renders the various tree edit controls (checkbox, tristate checkbox, text box etc.)"""
    def __init__(self, tree):
        TreeCellEditor.__init__(self)
        self.editor = None
        self.tree = tree

        flowLayout = FlowLayout(FlowLayout.LEFT, 0, 0)

        self.cbPanel = JPanel(flowLayout)
        self.cb = JCheckBox(actionPerformed = self.checked)
        self.cbPanel.add(self.cb)
        self.cbLabel = JLabel()
        self.cbPanel.add(self.cbLabel)

        self.tcbPanel = JPanel(flowLayout)
        self.tcb = TristateCheckBox(self.checked)
        self.tcbPanel.add(self.tcb)
        self.tcbLabel = JLabel()
        self.tcbPanel.add(self.tcbLabel)

        self.rbPanel = JPanel(flowLayout)
        self.rb = JRadioButton(actionPerformed = self.checked)
        self.rbPanel.add(self.rb)
        self.rbLabel = JLabel()
        self.rbPanel.add(self.rbLabel)

        self.tfPanel = JPanel(flowLayout)
        self.tfLabel = JLabel()
        self.tfPanel.add(self.tfLabel)
        self.tf = JTextField()
        self.tf.setColumns(12)
        self.tf.addActionListener(self)
        self.tfPanel.add(self.tf)

    def addCellEditorListener(self, l):
        """Register for edit events"""
        self.listener = l

    def isCellEditable(self, event):
        if event != None and isinstance(event.getSource(), JTree) and isinstance(event, MouseEvent):
            tree = event.getSource()
            path = tree.getPathForLocation(event.getX(), event.getY())
            userData = path.getLastPathComponent().getUserObject()
            if isinstance(userData, TreeNodeData) and (not userData.getNodeType().isType([NodeType._comment, NodeType._menu])) and (userData.getVisible() > 0):
                return True

        return False

    def shouldSelectCell(self, event):
        # log.info("shouldSelectCell")
        return True

    def cancelCellEditing(self):
        # log.info("Cancel editing, please!")
        # super(CustomCellEditor, self).cancelCellEditing()
        pass

    def stopCellEditing(self):
        # log.info("stopCellEditing")
        if self.nodeData.getNodeType().isType([NodeType._text]):
            # log.info("stopCellEditing for sure!")
            self.nodeData.setValue(str(self.tf.getText()))
        return True

    def getTreeCellEditorComponent(self, tree, value, selected, expanded, leaf, row):
        """Return a swing edit control appropriate for the node type of the supplied value"""
        self.nodeData = self.getNodeUserData(value)
        if self.nodeData:
            text = self.nodeData.getText()
            t = self.nodeData.getNodeType()

            # Boolean checkbox
            if t.isType([NodeType._bool]):
                self.editor = self.cbPanel
                self.cbLabel.setText(text)
                if self.nodeData.getTriValue() > 0:
                    self.cb.setSelected(True)
                else:
                    self.cb.setSelected(False)

            # Tristate checkbox
            elif t.isType([NodeType._tri]):
                # log.info("getTreeCellEditorComponent tristate")
                self.editor = self.tcbPanel
                self.tcbLabel.setText(text)
                self.tcb.setTriState(self.nodeData.getTriValue())

            # Radio button
            elif t.isType([NodeType._radio]):
                self.editor = self.rbPanel
                self.rbLabel.setText(text)
                if self.nodeData.getTriValue() > 0:
                    self.rb.setSelected(True)
                else:
                    self.rb.setSelected(False)

            # Text field
            elif t.isType([NodeType._text]):
                self.editor = self.tfPanel
                self.tfLabel.setText(str(self.nodeData.getText()) + ":")
                self.tf.setText(str(self.nodeData.getValue()))

            else:
                self.editor = self.tcb
                self.editor.setText(text)

        return self.editor

    def getNodeUserData(self, value):
        """Gets the TreeNodeData from the tree node"""
        if isinstance(value,  DefaultMutableTreeNode):
            nodeData = value.getUserObject()
            if isinstance(nodeData, TreeNodeData):
                return nodeData

        return None

    def getCellEditorValue(self):
        newNode = TreeNodeData(self.nodeData.knode, self.tree)

        if isinstance(self.editor, JTextField):
            newNode.setValue(str(self.editor.getText()))

        return newNode

    def checked(self, e):
        """Updates the node data when a checkbox has been clicked"""
        control = e.getSource()

        if isinstance(control, TristateCheckBox):
            # log.info("tristate checked")
            self.nodeData.setTriValue(control.getTriState())
        else:
            # log.info("checkbox checked")
            if control.isSelected():
                self.nodeData.setValue(2)
            else:
                self.nodeData.setValue(0)

    def actionPerformed(self, event):
        """ ENTER pressed in text field, stop editing."""
        tf = event.getSource()
        self.listener.editingStopped(ChangeEvent(tf))


class KConfigTree(JTree, CellEditorListener):
    """Custom Swing JTree based tree that visualizes a KConfig configuration.
        The full KConfig menu structure is put into a shadow tree model. From the shadow model,
        a real model is built (updateModel), where hidden nodes are not included. This update model
        is what the tree uses to visualize the configuration menu.
        Both the shadow and the updated model has the same TreeNodeData with KConfig data.
        The expanded state and search result state is kept in the TreeNodeData.
    """
    shadowModel = None
    isUpdating = False
    showAll = False
    isSearching = False

    def __init__(self, kconf):
        self.setCellRenderer(CustomCellRenderer())
        self.setCellEditor(CustomCellEditor(self))
        self.createKconfShadowModel(kconf)
        self.setModel(self.createUpdatedModel())
        self.expandRow(0)
        self.setEditable(True)
        self.setRootVisible(False)
        self.setShowsRootHandles(True)
        self.setRowHeight(0)
        self.addTreeExpansionListener(KConfigTreeExpansionListener())
        self.getCellEditor().addCellEditorListener(self)


    def editingCanceled(self, event):
        """From CellEditorListener """
        # log.info("editingCanceled", self.cellEditor.getCellEditorValue())
        pass

    def editingStopped(self, event):
        """From CellEditorListener."""
        # log.info("editingStopped", self.cellEditor.getCellEditorValue())
        self.stopEditing()

    def createKconfShadowModel(self, kconf):
        """Create the one and only shadow data model"""
        rootNode = DefaultMutableTreeNode(kconf.mainmenu_text)
        self.addNodes(rootNode, kconf.top_node.list)
        self.shadowModel = DefaultTreeModel(rootNode)

    def addNodes(self, parent, node):
        """Recursively traverse the KConfig structure and add to the shadow model"""
        while node:
            newUiNode = DefaultMutableTreeNode(TreeNodeData(node, self))
            parent.add(newUiNode)

            if node.list:
                self.addNodes(newUiNode, node.list)

            node = node.next

    def createUpdatedModel(self):
        """When the user does any changes in the tree, the underlaying kconfig structure
        will change. Nodes may change visibility and value. The tree control cannot hide nodes,
        so a new datamodel must be generated that does not include invisible nodes."""
        shadowTreeRoot = self.shadowModel.getRoot()
        rootNode = DefaultMutableTreeNode("Root")
        self.addVisibleNodes(rootNode, shadowTreeRoot)
        return DefaultTreeModel(rootNode)

    def addVisibleNodes(self, visibleParent, shadowParent):
        """Adds visible nodes from the shadow tree model to the update tree model.
        If there is an active search operation, only search matches will be added.
        If showAll is set, all nodes are added regardless of visibility."""
        childrenEnum = shadowParent.children()
        while childrenEnum.hasMoreElements():
            shadowChild = childrenEnum.nextElement()

            if shadowChild.getUserObject().getVisible() > 0 or self.showAll:
                if not self.isSearching or shadowChild.getUserObject().isSearchMatch():
                    visibleChild = DefaultMutableTreeNode(shadowChild.getUserObject())
                    visibleParent.add(visibleChild)

                    if shadowChild.getChildCount() > 0:
                        self.addVisibleNodes(visibleChild, shadowChild)

    def isPathEditable(self, path):
        comp = path.getLastPathComponent()
        if isinstance(comp, DefaultMutableTreeNode):
            nodeData = comp.getUserObject()
            if isinstance(nodeData, TreeNodeData):
                return True
        return False

    def updateTree(self):
        """Call to create a new updated tree model"""
        if not self.isUpdating:
            # log.info("updateTree()")
            self.isUpdating = True
            self.setModel(self.createUpdatedModel())
            self.updateExpandedState(self.getModel().getRoot())
            self.isUpdating = False

    def updateExpandedState(self, parent):
        """Scan through the whole tree and expand the tree node
        if the node data has the expanded field set to True."""
        childrenEnum = parent.children()
        while childrenEnum.hasMoreElements():
            child = childrenEnum.nextElement()

            if child.getUserObject().isExpanded():
                self.expandPath(TreePath(child.getPath()))

            if child.getChildCount() > 0:
                self.updateExpandedState(child)

    def setShowAll(self, show):
        self.showAll = show
        self.updateTree()

    def doSearch(self, searchText):
        """Perform a search in the data model with the supplied text."""
        if len(searchText) > 0:
            self.isSearching = True
            self.doSearchBranch(self.shadowModel.getRoot(), searchText)
        else:
            self.isSearching = False
        self.updateTree()

    def doSearchBranch(self, shadowParent, searchText):
        """Traverse the tree model searching for the search text"""
        match = False

        childrenEnum = shadowParent.children()
        while childrenEnum.hasMoreElements():
            shadowChild = childrenEnum.nextElement()

            if shadowChild.getUserObject().search(searchText, self.showAll):
                match = True

            if shadowChild.getChildCount() > 0:
                if self.doSearchBranch(shadowChild, searchText):
                    shadowChild.getUserObject().setSearchMatch(True)
                    match = True

        return match


class KConfigTreeExpansionListener(TreeExpansionListener):
    """Listener for tree expand/collapse events. Used for storing the expand state
    in the node data, so that a new updated tree's branches can be expanded the same way
    as in the old tree."""
    def treeExpanded(self, e):
        if not e.getPath().getLastPathComponent() == e.getSource().getModel().getRoot():
            e.getPath().getLastPathComponent().getUserObject().setExpanded(True)

    def treeCollapsed(self, e):
        if not e.getPath().getLastPathComponent() == e.getSource().getModel().getRoot():
            e.getPath().getLastPathComponent().getUserObject().setExpanded(False)


class MPConfig(TreeSelectionListener):
    """The MPConfig component initializes the KConfig library with the requested configuration,
    and buildst the GUI, consisting of a "Load" and a "Save as" buttons, a search field, "show all"
    checkbox, tree view and information text view."""
    def __init__(self, kconfig_file = "Kconfig", config_file=".config", systemLogger = None):
        """[summary]

        Parameters
        ----------
            kconfig_file : string (default: "Kconfig")
                The Kconfig configuration file
            config_file : string (default: ".config")
                The save file which will be used for loading and saving the settings
            systemLogger (default: None)
                A system logger object. If None then print statements are used for logging.
        """
        global log
        if systemLogger:
            log = systemLogger

        # Load Kconfig configuration files
        self.kconfig = Kconfig(kconfig_file)
        setKConfig(self.kconfig)

        if os.path.isfile(config_file):
            log.info(self.kconfig.load_config(config_file))
        elif os.path.isfile(".config"):
            log.info(self.kconfig.load_config(".config"))

        self.tree = KConfigTree(self.kconfig)
        self.tree.addTreeSelectionListener(self.treeSelectionChanged)
        jTreeSP = JScrollPane(self.tree)

        self.jta = JTextArea()
        self.jta.setEditable(False)
        jTextSP = JScrollPane(self.jta)

        toolPanel = JPanel()
        toolPanel.setLayout(BoxLayout(toolPanel, BoxLayout.X_AXIS))
        toolPanel.setBorder(BorderFactory.createEmptyBorder(2, 0, 2, 0))

        toolPanel.add(JLabel("Search: "))

        jSearchPanel = JPanel()
        jSearchPanel.setLayout(BoxLayout(jSearchPanel, BoxLayout.X_AXIS))
        self.jSearchField = JTextField()
        jSearchPanel.setBackground(self.jSearchField.getBackground())
        jSearchPanel.setBorder(self.jSearchField.getBorder())
        self.jSearchField.setBorder(None)
        self.jSearchField.getDocument().addDocumentListener(SearchListener(self.tree))
        jSearchPanel.add(self.jSearchField)

        clearSearchButton = JButton(u'\u00d7', actionPerformed = self.clearSearch)
        d = clearSearchButton.getPreferredSize()
        clearSearchButton.setPreferredSize(Dimension(d.height, d.height))
        clearSearchButton.setBackground(self.jSearchField.getBackground())
        clearSearchButton.setBorder(None)
        clearSearchButton.setOpaque(False)
        clearSearchButton.setContentAreaFilled(False)
        clearSearchButton.setFocusPainted(False)
        jSearchPanel.add(clearSearchButton)

        toolPanel.add(jSearchPanel)

        self.showAllCheckBox = JCheckBox("Show all", actionPerformed = self.OnShowAllCheck)
        toolPanel.add(self.showAllCheckBox)


        splitPane = JSplitPane(JSplitPane.VERTICAL_SPLIT, jTreeSP, jTextSP)
        splitPane.setOneTouchExpandable(True)
        splitPane.setDividerLocation(300)

        treePanel = JPanel(BorderLayout())
        treePanel.add(toolPanel, BorderLayout.NORTH)
        treePanel.add(splitPane, BorderLayout.CENTER)

        loadSavePanel = JPanel()
        loadSavePanel.setLayout(BoxLayout(loadSavePanel, BoxLayout.X_AXIS))
        loadSavePanel.add(JButton("Load", actionPerformed=self.loadConfigDialog))
        loadSavePanel.add(JButton("Save as", actionPerformed=self.writeConfigDialog))

        self.rootPanel = JPanel()
        self.rootPanel.setLayout(BorderLayout())
        self.rootPanel.add(loadSavePanel, BorderLayout.PAGE_START)
        self.rootPanel.add(treePanel, BorderLayout.CENTER)

    def clearSearch(self, event):
        self.jSearchField.setText("")

    def OnShowAllCheck(self, event):
        self.tree.setShowAll(self.showAllCheckBox.isSelected())
        self.tree.doSearch(self.jSearchField.getText()) # Must repeat the search if one is active

    def treeSelectionChanged(self, event):
        """When the user selects a new node in the tree, show info about the selected node
        in the info text area below the tree."""
        path = event.getNewLeadSelectionPath()
        if path:
            comp = path.getLastPathComponent()
            if isinstance(comp, DefaultMutableTreeNode):
                nodeData = comp.getUserObject()
                if isinstance(nodeData, TreeNodeData):
                    self.jta.setText(getNodeInfoString(nodeData.knode))
                    self.jta.setCaretPosition(0)

    def getPane(self):
        """Return the panel containing all the other components that is set up in __init__()."""
        return self.rootPanel

    def writeConfig(self, fileName):
        """Write the current configuration to the file specified."""
        self.kconfig.write_config(fileName) # Save full configuration
        #self.kconfig.write_min_config(fileName) # Save minimal configuration

    def loadConfig(self, fileName):
        """Load configuration settings from the file specified."""
        if os.path.isfile(fileName):
            log.info(self.kconfig.load_config(fileName))
            self.tree.createKconfShadowModel(self.kconfig)
            self.tree.updateTree()

    def writeConfigDialog(self, e):
        """Open a file dialog to save configuration"""
        fileChooser = JFileChooser(os.getcwd())
        retval = fileChooser.showSaveDialog(None)
        if retval == JFileChooser.APPROVE_OPTION:
            f = fileChooser.getSelectedFile()
            self.writeConfig(f.getPath())

    def loadConfigDialog(self, e):
        """Open a file dialog to select configuration to load"""
        fileChooser = JFileChooser(os.getcwd())
        retval = fileChooser.showOpenDialog(None)
        if retval == JFileChooser.APPROVE_OPTION:
            f = fileChooser.getSelectedFile()
            log.info("Selected file: " + f.getPath())
            self.loadConfig(f.getPath())


class SearchListener(DocumentListener):
    """Triggered when the user adds or removes characters in the search text field."""
    def __init__(self, tree):
        self.tree = tree

    def changedUpdate(self, e):
        doc = e.getDocument()
        searchText = doc.getText(0, doc.getLength())
        self.tree.doSearch(searchText)

    def insertUpdate(self, e):
        self.changedUpdate(e)

    def removeUpdate(self, e):
        self.changedUpdate(e)


if __name__ == "__main__":
    # Set default .config file or load it from argv
    if len(sys.argv) == 2:
        # Specify "Kconfig"
        mpconfig = MPConfig(sys.argv[1])
    else:
        # Specify "Kconfig" and ".config"
        mpconfig = MPConfig(sys.argv[1], sys.argv[2])

    jframe = JFrame("MPLAB X Kconfig Editor")
    jframe.getContentPane().add(mpconfig.getPane())

    jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE)
    jframe.setSize(500, 800)
    jframe.setVisible(True)
