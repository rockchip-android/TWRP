/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _NETLINKHANDLER_H
#define _NETLINKHANDLER_H

#include "NetlinkListener.h"

class NetLinkBroadcaster{
public:
    virtual ~NetLinkBroadcaster() = default;
    virtual void onNetLinkStart() = 0;
    virtual void onMessageReceive(NetlinkEvent *evt) = 0;
};

class NetlinkHandler: public NetlinkListener {

public:
    NetLinkBroadcaster* mBroadcaster;
    explicit NetlinkHandler(int listenerSocket, NetLinkBroadcaster* broadcaster);
    virtual ~NetlinkHandler();

    int start(void);
    int stop(void);

protected:
    virtual void onEvent(NetlinkEvent *evt);
};
#endif
