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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//#include <android-base/logging.h>

#include "../../twcommon.h"
#include "NetlinkEvent.h"
#include "NetlinkHandler.h"
//#include "VolumeManager.h"

NetlinkHandler::NetlinkHandler(int listenerSocket, NetLinkBroadcaster* broadcaster) :
                NetlinkListener(listenerSocket) {
    mBroadcaster = broadcaster;
}

NetlinkHandler::~NetlinkHandler() {
}

int NetlinkHandler::start() {
    return this->startListener();
}

int NetlinkHandler::stop() {
    return this->stopListener();
}

void NetlinkHandler::onEvent(NetlinkEvent *evt) {
    const char *subsys = evt->getSubsystem();

    if (!subsys) {
        SLOGW("No subsystem found in netlink event");
        return;
    }

//    SLOGW("Subsystem:%s", subsys);
//    SLOGW("Action   :%d", evt->getAction());
//    evt->dump();

    if(mBroadcaster){
        mBroadcaster->onMessageReceive(evt);
    }
}
