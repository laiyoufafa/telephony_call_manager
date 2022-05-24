/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "rejectcall_fuzzer.h"
#include <cstddef>
#include <cstdint>
#include "call_manager_client.h"
#include "system_ability_definition.h"

using namespace OHOS::Telephony;
namespace OHOS {
    void DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
    {
        if (data == nullptr || size <= 0) {
            return;
        }
        auto cmClient = DelayedSingleton<CallManagerClient>::GetInstance();
        if (!cmClient) {
            return;
        }

        cmClient->Init(TELEPHONY_CALL_MANAGER_SYS_ABILITY_ID);
        std::string number(reinterpret_cast<const char*>(data), size);
        cmClient->RejectCall(size, true, Str8ToStr16(number));
        cmClient->RejectCall(size, false, Str8ToStr16(number));
    }
}  // namespace OHOS

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}
