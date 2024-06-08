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

#include <ParGen.hpp>
#include <Util.hpp>
#include <exception.hpp>

#include <list>
#include <variant>
#include <unordered_map>
#include <functional>

using namespace Pargen;

void resolve_use(std::list<std::variant<Rule, Group>>& rules){

    std::unordered_map<std::string, Rule> rule_map;

    std::function<void(std::list<std::variant<Rule, Use, Group>>&)> collect_rule = 
        [&collect_rule, &rule_map](std::list<std::variant<Rule, Use, Group>>& group)
    {
        for(std::variant<Rule, Use, Group>& elem : group){
            std::visit(overloaded {
                [&](Rule& rule){
                    if(!rule.id.empty()){
                        rule_map[rule.id] = rule;
                    }
                },
                [&](Group& group){
                    collect_rule(group);
                },
                [](Use&){}
            }, elem);
        }
    };

    std::function<void(std::list<std::variant<Rule, Use, Group>>&)> resolve_state_use = 
        [&resolve_state_use, &rule_map](std::list<std::variant<Rule, Use, Group>>& group)
    {
        for(std::variant<Rule, Use, Group>& elem : group){
            std::visit(overloaded {
                [&](Group& gr){
                    resolve_state_use(gr);
                },
                [&](Use& use){
                    if(rule_map.contains(use.id)){
                        elem.emplace<Rule>(rule_map[use.id]);
                    }else{
                        throw Exception::Exception("rule id '" + use.id + "' not exist");
                    }
                },
                [](Rule&){}
            }, elem);
        }
    };

    for(std::variant<Rule, Group>& elem : rules){
        std::visit(overloaded {
            [&](Rule& rule){
                if(!rule.id.empty()){
                    rule_map[rule.id] = rule;
                }
            },
            [&](Group& group){
                collect_rule(group);
            }
        }, elem);
    }
    for(std::variant<Rule, Group>& elem : rules){
        std::visit(overloaded {
            [](Rule&){},
            [&](Group& group){
                resolve_state_use(group);
            }
        }, elem);
    }
}
