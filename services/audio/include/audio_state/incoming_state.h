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

#ifndef TELEPHONY_INCOMING_STATE_H
#define TELEPHONY_INCOMING_STATE_H

#include "audio_base.h"

namespace OHOS {
namespace Telephony {
class IncomingState : public AudioBase {
public:
    IncomingState() = default;
    ~IncomingState() = default;
    bool ProcessEvent(int32_t event) override;
};
} // namespace Telephony
} // namespace OHOS
#endif // TELEPHONY_INCOMING_STATE_H