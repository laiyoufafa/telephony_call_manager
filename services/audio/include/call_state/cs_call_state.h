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

#ifndef CS_CALL_STATE_H
#define CS_CALL_STATE_H
#include "audio_state.h"

namespace OHOS {
namespace TelephonyCallManager {
class CSCallState : public AudioState {
public:
    CSCallState() = default;
    ~CSCallState() = default;
    void StateBegin(const std::string msg) override;
    void StateProcess(int32_t event) override;
    void StateEnd(const std::string msg) override;
    void HandleNoneAlertingOrActiveCall();
    void HandleNoneRingingCall();

private:
    std::mutex mutex_;
};
} // namespace TelephonyCallManager
} // namespace OHOS
#endif // CS_CALL_STATE_H