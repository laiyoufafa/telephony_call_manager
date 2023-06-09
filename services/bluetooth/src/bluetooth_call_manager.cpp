/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bluetooth_call_manager.h"

#include "call_manager_errors.h"
#include "telephony_log_wrapper.h"

#include "audio_control_manager.h"
#include "call_control_manager.h"
#include "bluetooth_connection.h"

#ifdef ABILITY_BLUETOOTH_SUPPORT
#include "bluetooth_mgr_client.h"
#include "bluetooth_remote_device.h"
#endif

namespace OHOS {
namespace Telephony {
BluetoothCallManager::BluetoothCallManager() : btConnection_(std::make_unique<BluetoothConnection>()) {}

BluetoothCallManager::~BluetoothCallManager() {}

bool BluetoothCallManager::ConnectBtSco()
{
    if (btConnection_ == nullptr) {
        TELEPHONY_LOGE("bluetooth connection nullptr");
        return false;
    }
    return btConnection_->ConnectBtSco();
}

bool BluetoothCallManager::DisconnectBtSco()
{
    if (btConnection_ == nullptr) {
        TELEPHONY_LOGE("bluetooth connection nullptr");
        return false;
    }
    return btConnection_->DisconnectBtSco();
}

int32_t BluetoothCallManager::SendBtCallState(
    int32_t numActive, int32_t numHeld, int32_t callState, const std::string &number)
{
    if (btConnection_ == nullptr) {
        TELEPHONY_LOGE("bluetooth connection nullptr");
        return false;
    }
    return btConnection_->SendBtCallState(numActive, numHeld, callState, number);
}

BtScoState BluetoothCallManager::GetBtScoState()
{
    if (btConnection_ == nullptr) {
        TELEPHONY_LOGE("bluetooth connection nullptr");
        return BtScoState::SCO_STATE_UNKNOWN;
    }
    return btConnection_->GetBtScoState();
}

bool BluetoothCallManager::IsBtScoConnected()
{
    if (btConnection_ == nullptr) {
        TELEPHONY_LOGE("bluetooth connection nullptr");
        return false;
    }
    return btConnection_->IsBtScoConnected();
}
} // namespace Telephony
} // namespace OHOS