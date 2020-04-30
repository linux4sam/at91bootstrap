from __future__ import unicode_literals

from java.util import EventListener

_wrapperClassMap = {}  # event interface name -> wrapper class


def _noOp(self, event):
    pass


def _createListenerWrapper(eventInterface, eventNames, listener, args, kwargs,
                           removeMethod):
    eventNames = ((eventNames,) if isinstance(eventNames, basestring) else
                  sorted(eventNames))
    assert issubclass(eventInterface, EventListener), \
        'eventName class must be a subclass of EventListener'
    assert hasattr(listener, '__call__'), 'listener must be callable'
    for eventName in eventNames:
        assert hasattr(eventInterface, eventName), \
            '%s has no method named "%s"' % \
            (eventInterface.__name__, eventName)

    # Figure out the fully qualified name of the interface
    className = eventInterface.__name__
    if eventInterface.__module__:
        className = eventInterface.__module__ + '.' + className
    mapKey = '%s/%s' % (className, ','.join(eventNames))

    # Create a wrapper class for this eventName class if it's not there yet
    wrapperClass = _wrapperClassMap.get(mapKey)
    if not wrapperClass:
        # Gather all the interface methods
        methodNames = set()
        for cls in eventInterface.__mro__:
            if cls is EventListener:
                break
            methodNames.update(m for m in cls.__dict__ if
                               not m.startswith('_'))

        # Redirect all interface methods to self.handleEvent()
        methods = {m: EventListenerWrapper.handleEvent
                   if m in eventNames else _noOp for m in methodNames}
        wrapperClass = type('%sWrapper' % eventInterface.__name__,
                            (EventListenerWrapper, eventInterface), methods)
        _wrapperClassMap[mapKey] = wrapperClass

    return wrapperClass(listener, args, kwargs, removeMethod)


class EventListenerWrapper(object):
    def __init__(self, listener, args, kwargs, removeMethod):
        self.listener = listener
        self.args = args
        self.kwargs = kwargs
        self.removeMethod = removeMethod
        self.removeMethodArgs = (self,)

    def handleEvent(self, event):
        self.listener(event, *self.args, **self.kwargs)

    def unlisten(self):
        self.removeMethod(*self.removeMethodArgs)


def addEventListener(target, eventInterface, event, listener, *args, **kwargs):
    """
    Adds an event listener to `target`.

    :param target: an object that supports listening to the events of the given
                   type (the add*Listener methods must be inherited from a Java
                   class so that autodetection will work)
    :param eventInterface: the interface that the listener wrapper has to
                           implement (e.g. :class:`java.awt.MouseListener`)
    :param event: name(s) of the event(s) to listen for (e.g. "mouseClicked")
    :param listener: callable that is called with ``(event, *args, **kwargs)``
                     when the event is fired
    :type eventInterface: Java interface
    :type event: string or an iterable of strings
    :type listener: callable
    :return: the listener wrapper that you can use to stop listening to these
             events (with :meth:`~EventListenerWrapper.unlisten`)

    """
    addMethodName = 'add%s' % eventInterface.__name__
    addMethod = getattr(target, addMethodName)
    removeMethodName = 'remove%s' % eventInterface.__name__
    removeMethod = getattr(target, removeMethodName)
    wrapper = _createListenerWrapper(eventInterface, event, listener, args,
                                     kwargs, removeMethod)
    addMethod(wrapper)
    return wrapper


def addPropertyListener(target, property, listener, *args, **kwargs):
    """
    Adds a callback that is called when the given property has changed.
    A listener can either listen to changes in a specific property,
    or all properties (by supplying `None` as the property name).
    The listener is called with ``(event, *args, **kwargs)``.

    :param target: the object whose property will be listened to
    :param property: name of the property, or None to listen to all
                     property changes
    :type listener: function or any callable
    :return: the listener wrapper that you can use to stop listening to these
             events (with obj.removePropertyChangeListener())

    """
    from java.beans import PropertyChangeListener
    wrapper = _createListenerWrapper(
        PropertyChangeListener, 'propertyChange', listener, args, kwargs,
        target.removePropertyChangeListener)
    add_args = (wrapper,) if property is None else (property, wrapper)
    wrapper.removeMethodArgs = add_args
    target.addPropertyChangeListener(*add_args)
    return wrapper


#
# Shortcuts for java.awt.event
#

def addActionListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, ActionListener, 'actionPerformed',
    listener).

    """
    from java.awt.event import ActionListener
    return addEventListener(target, ActionListener, 'actionPerformed',
                            listener, *args, **kwargs)


def addItemListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, ItemListener, 'itemStateChanged',
    listener).

    """
    from java.awt.event import ItemListener
    return addEventListener(target, ItemListener, 'itemStateChanged', listener,
                            *args, **kwargs)


def addFocusLostListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, FocusListener, 'focusLost',
    listener).

    """
    from java.awt.event import FocusListener
    return addEventListener(target, FocusListener, 'focusLost', listener,
                            *args, **kwargs)


def addMouseClickListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, MouseListener, 'mouseClicked',
    listener).

    """
    from java.awt.event import MouseListener
    return addEventListener(target, MouseListener, 'mouseClicked', listener,
                            *args, **kwargs)


#
# Shortcuts for javax.swing.events
#

def addCaretListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, CaretListener, 'caretUpdate',
    listener).

    """
    from javax.swing.event import CaretListener
    return addEventListener(target, CaretListener, 'caretUpdate', listener,
                            *args, **kwargs)


def addChangeListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, ChangeListener, 'stateChanged',
    listener).

    """
    from javax.swing.event import ChangeListener
    return addEventListener(target, ChangeListener, 'stateChanged', listener,
                            *args, **kwargs)


def addDocumentListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, DocumentListener,
    ('insertUpdate', 'removeUpdate', 'changedUpdate'), listener).
    """
    from javax.swing.event import DocumentListener

    events = ('insertUpdate', 'removeUpdate', 'changedUpdate')
    return addEventListener(target, DocumentListener, events, listener, *args,
                            **kwargs)


def addListDataListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, ListDataListener,
    ('contentsChanged', 'intervalAdded', 'intervalRemoved'), listener).
    """
    from javax.swing.event import ListDataListener

    events = ('contentsChanged', 'intervalAdded', 'intervalRemoved')
    return addEventListener(target, ListDataListener, events, listener, *args,
                            **kwargs)


def addListSelectionListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, ListSelectionListener,
    'valueChanged', listener).

    """
    from javax.swing.event import ListSelectionListener
    return addEventListener(target, ListSelectionListener, 'valueChanged',
                            listener, *args, **kwargs)


def addRowSorterListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, addTreeSelectionListener,
    'sorterChanged', listener).

    """
    from javax.swing.event import RowSorterListener
    return addEventListener(target, RowSorterListener, 'sorterChanged',
                            listener, *args, **kwargs)


def addTableModelListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, TableModelListener,
    'tableChanged', listener).

    """
    from javax.swing.event import TableModelListener
    return addEventListener(target, TableModelListener, 'tableChanged',
                            listener, *args, **kwargs)


def addTreeSelectionListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, TreeSelectionListener,
    'valueChanged', listener).

    """
    from javax.swing.event import TreeSelectionListener
    return addEventListener(target, TreeSelectionListener, 'valueChanged',
                            listener, *args, **kwargs)


def addUndoableEditListener(target, listener, *args, **kwargs):
    """
    Shortcut for addEventListener(target, UndoableEditListener,
    'undoableEditHappened', listener).

    """
    from javax.swing.event import UndoableEditListener
    return addEventListener(target, UndoableEditListener,
                            'undoableEditHappened', listener, *args, **kwargs)
