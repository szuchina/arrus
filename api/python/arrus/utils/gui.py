import matplotlib.pyplot as plt
import numpy as np
import time
from matplotlib.animation import FuncAnimation


class Display2DParams:
    """
    The class describig parameters for Display2D class.

    """


    def __init__(self, metadata, value_range=None,
                 window_size=None, title=None, xlabel=None,
                 ylabel=None, cmap=None, interval=10,
                 input_timeout=2):
        """
        2D display constructor.

        :param value_range: range of values to display, (vmin, vmax)
        :param window_size: size of the window
        :param title: window title
        :param xlabel: x label
        :param ylabel: y label
        :param cmap: color map to apply
        :param interval: number of milliseconds between successive img updates
        """
        self.metadata = metadata
        self.window_size = window_size
        self.value_range = value_range
        self.title = title
        self.xlabel = xlabel
        self.ylabel = ylabel
        self.cmap = cmap
        self.input_timeout = input_timeout
        self.interval = interval
        self._prepare(metadata)
        self._current_queue = None
        self._anim = None






class Display2D:
    """
    A very simple implementation of the 2D display.

    Currently, implemented using matplotlib FuncAnimation.

    """
    '''
    def __init__(self, metadata, value_range=None,
                 window_size=None, title=None, xlabel=None,
                 ylabel=None, cmap=None, interval=10,
                 input_timeout=2):
        """
        2D display constructor.

        :param value_range: range of values to display, (vmin, vmax)
        :param window_size: size of the window
        :param title: window title
        :param xlabel: x label
        :param ylabel: y label
        :param cmap: color map to apply
        :param interval: number of milliseconds between successive img updates
        """
        self.metadata = metadata
        self.window_size = window_size
        self.value_range = value_range
        self.title = title
        self.xlabel = xlabel
        self.ylabel = ylabel
        self.cmap = cmap
        self.input_timeout = input_timeout
        self.interval = interval
        self._prepare(metadata)
        self._current_queue = None
        self._anim = None
        '''
    def __init__(self, params):
        """
         :param params: list of Display2DParams objects

        """

       self.params = params


    def _prepare(self):
        nplots = len(self.params)
        
        for iparam in range(nplots):

            self.params[iparam]._fig, self.params[iparam]._ax = plt.subplots()
            if self.params[iparam].window_size is not None:
                self.params[iparam]._fig.set_size_inches(self.window_size)
            if self.params[iparam].xlabel is not None:
                self.params[iparam]._ax.set_xlabel(self.xlabel)
            if self.params[iparam].ylabel is not None:
                self.params[iparam]._ax.set_ylabel(self.ylabel)
            if self.params[iparam].title is not None:
                self.params[iparam]._fig.canvas.set_window_title(self.title)


            input_shape = self.params[iparam].metadata.input_shape
            datatype = self.params[iparam].metadata.dtype
            empty = np.zeros(input_shape, dtype=datatype)
            if self.params[iparam].value_range:
                vmin, vmax = self.params[iparam].value_range
                self._img = self.params[iparam]._ax.imshow(
                            empty,
                            cmap=self.params[iparam].cmap,
                            vmin=vmin,
                            vmax=vmax)
            else:
                # determine min max based on min max value of the input data type
                if np.issubdtype(empty.dtype, np.floating):
                    finfo = np.finfo(empty.dtype)
                    vmin, vmax = finfo.min, finfo.max
                elif np.issubdtype(empty.dtype, np.integer):
                    iinfo = np.iinfo(empty.dtype)
                    vmin, vmax = iinfo.min, iinfo.max
                else:
                    raise ValueError(f"Unsupported data type: {empty.dtype}")
                self.params[iparam]._img = self.params[iparam]._ax.imshow(
                                                                        empty,
                                                                        cmap=self.cmap,
                                                                        vmin=vmin,
                                                                        vmax=vmax)
                pass

    def start(self, queues):
        nqueues = len(queues)
        for iqueue in range(nqueues):
            queue = queues[iqueue]
            self._current_queue[iqueue] = queue
            self._anim[iqueue] = FuncAnimation(self.params[iqueue]._fig, self._update,
                                   interval=self.params[iqueue].interval)
            plt.show()

    def _update(self, frame):
        nqueues = len(self._current_queue)
        for iqueue in range(nqueues):
            data = self._current_queue[iqueue].get(timeout=self.input_timeout)
            self.params[iqueue]._img.set_data(data)
