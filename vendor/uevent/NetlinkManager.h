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

#ifndef _NETLINKMANAGER_H
#define _NETLINKMANAGER_H

#include <vector>

#include "SocketListener.h"
#include "NetlinkListener.h"
#include "NetlinkHandler.h"

class NetlinkHandler;

class INetLinkReceive{
public:
    virtual ~INetLinkReceive() = default;
    virtual bool onMessage(NetlinkEvent *evt) = 0;
};

class NetlinkManager : public NetLinkBroadcaster{
private:
    static NetlinkManager *sInstance;

private:
    SocketListener       *mBroadcaster;
    NetlinkHandler       *mHandler;
    int                  mSock;
    std::vector<INetLinkReceive*> mListens;

public:
    virtual ~NetlinkManager();

    int start();
    int stop();

    void onNetLinkStart() override;
    void onMessageReceive(NetlinkEvent *evt) override;

    void setBroadcaster(SocketListener *sl) { mBroadcaster = sl; }
    SocketListener *getBroadcaster() { return mBroadcaster; }
    void addListen(INetLinkReceive* receive);
    void removeListen(INetLinkReceive* receive);

    static NetlinkManager *Instance();

private:
    NetlinkManager();
};
#endif
