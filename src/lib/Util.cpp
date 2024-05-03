// Copyright 2024 Luis Hsu
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     https://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <Util.hpp>

std::string strip(std::string str, bool lead, bool trail){
    size_t lead_pos = lead ? str.find_first_not_of(" \t\n\r\v") : 0;
    if(trail){
        size_t trail_pos = str.find_last_not_of(" \t\n\r\v");
        return str.substr(lead_pos, trail_pos - lead_pos + 1);
    }else{
        return str.substr(lead_pos);
    }
}