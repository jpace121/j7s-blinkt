// Copyright 2020 James Pace
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <chrono>
#include <thread>
#include "blinkt_interface/blinkt.hpp"
#include "blinkt_interface/color.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;

    blinkt_interface::Blinkt blinkt{};

    for (auto & pixel : blinkt.getPixelArray())
    {
        pixel = blinkt_interface::color::red(0.5);
        blinkt.display();
        std::this_thread::sleep_for(1s);
        pixel = blinkt_interface::color::off(0.5);
    }
    return 0;
}
