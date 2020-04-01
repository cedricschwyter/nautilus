#ifndef NAUTILUS_STATUS_HPP
#define NAUTILUS_STATUS_HPP

enum NautilusStatus {
    NAUTILUS_STATUS_OK                          = 0,
    NAUTILUS_STATUS_FATAL                       = -1,
    NAUTILUS_STATUS_SWAPCHAIN_RECREATED         = NAUTILUS_STATUS_OK
};

#endif      // NAUTILUS_STATUS_HPP