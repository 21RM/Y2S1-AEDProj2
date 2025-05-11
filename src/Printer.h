//
// Created by master on 24-12-2023.
//

#ifndef AED_PROJ_2_PRINTER_H
#define AED_PROJ_2_PRINTER_H

#endif //AED_PROJ_2_PRINTER_H

#include <iostream>
#include <vector>
#include "Util.h"
#include "Airline.h"

//----------------- COLOR SCHEMES --------------------//
std::wstring bg_light_red = L"\x1b[101m";
std::wstring end_bg = L"\x1b[0m";
std::wstring italic = L"\x1b[3m";
std::wstring end_italic = L"\x1b[0m";
std::wstring red = L"\033[31m";
std::wstring bold = L"\033[1m";
std::wstring underline = L"\033[4m";;
std::wstring end_effect = L"\033[0m";
//----------------------------------------------------//

std::vector<std::vector<std::wstring>> loadingDataAnimation = {
        {
                L"█   ████  ██  ███  ███ ██  █  ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  _    █  █ █__█  █  █__█   █         ",
                L"███ ████ █  █ ███  ███ █  ██  ████    ███  █  █  █  █  █      █  █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █  ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  _    █  █ █__█  █  █__█      █      ",
                L"███ ████ █  █ ███  ███ █  ██  ████    ███  █  █  █  █  █   █     █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █  ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  _    █  █ █__█  █  █__█         █   ",
                L"███ ████ █  █ ███  ███ █  ██  ████    ███  █  █  █  █  █   █  █     █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █  ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  _    █  █ █__█  █  █__█            █",
                L"███ ████ █  █ ███  ███ █  ██  ████    ███  █  █  █  █  █   █  █  █   ",
        },
        {
                L"█   ████  ██  ███  ███ ██  █  ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  _    █  █ █__█  █  █__█             ",
                L"███ ████ █  █ ███  ███ █  ██  ████    ███  █  █  █  █  █   █  █  █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █  ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  _    █  █ █__█  █  █__█             ",
                L"███ ████ █  █ ███  ███ █  ██  ████    ███  █  █  █  █  █   █  █  █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █  ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  _    █  █ █__█  █  █__█             ",
                L"███ ████ █  █ ███  ███ █  ██  ████    ███  █  █  █  █  █   █  █  █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █  ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  _    █  █ █__█  █  █__█             ",
                L"███ ████ █  █ ███  ███ █  ██  ████    ███  █  █  █  █  █   █  █  █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █  ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  _    █  █ █__█  █  █__█             ",
                L"███ ████ █  █ ███  ███ █  ██  ████    ███  █  █  █  █  █   █  █  █  █",
        }
};

int space_size_for_animation = 0;

int space_size_increaser = 8;

int frame = 0;


std::wstring centerUp(const std::wstring& txtToCenter){
    if (getTerminalWidth() / 2 - txtToCenter.size() / 2 > 0){
        return std::wstring(getTerminalWidth() / 2 - txtToCenter.size() / 2, L' ') + txtToCenter;

    }
    return txtToCenter;
}

std::wstring centerUpAndLineUp(const std::wstring& txtToCenter, int lineUp){
    if (getTerminalWidth() / 2 - lineUp > 0){
        return std::wstring(getTerminalWidth() / 2 - lineUp, L' ') + txtToCenter;

    }
    return txtToCenter;
}


void printAnimatedAirplane(const std::vector<std::wstring>& draw, int sleep){
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    system("clear");
    for (const std::wstring& title_segment : draw){
        if (getTerminalWidth() - space_size_for_animation + draw[0].size() <= draw[0].size()) {
            std::wcout << std::wstring(space_size_for_animation - draw[0].size(), L' ');
            std::wcout << bold << title_segment.substr(0, getTerminalWidth() + draw[0].size() - space_size_for_animation)
                       << end_effect << std::endl;
        }
        else if (draw[0].size() >= space_size_for_animation){
            std::wcout << bold
                       << title_segment.substr(draw[0].size() - space_size_for_animation - 1, space_size_for_animation)
                       << end_effect << std::endl;
        }
        else{
            std::wcout << wstring(space_size_for_animation - draw[0].size(), L' ');
            std::wcout << bold << title_segment << end_effect << std::endl;
        }
    }
    space_size_for_animation += space_size_increaser;
    if (space_size_for_animation >= getTerminalWidth() + draw[0].size()){
        space_size_for_animation = 0;
    }
}


void printBoldTitle(const std::vector<std::wstring>& title){
    for (const std::wstring& title_segment : title){
        std::wcout << bold << title_segment << end_effect << std::endl;
    }
}

void printCenteredTitle(const std::vector<std::wstring>& title){
    for (const std::wstring& title_segment : title){
        std::wcout << bold << centerUp(title_segment) << end_effect << std::endl;
    }
}

void printTextLoadingData(){
    std::wcout << L"\n\n\n" << std::endl;
    printCenteredTitle(loadingDataAnimation[frame]);
    frame ++;
    if (frame > loadingDataAnimation.size() - 1){frame = 0;}
}

void printOptions(const std::vector<std::wstring>& options, unsigned long selected, bool table_mode){
    for(const std::wstring& s : options){
        if (s == options[selected] && !table_mode){
            std::wcout << "< " << underline << bold << red << s << end_effect << L" >" << std::endl << L"\n";
        }
        else{
            std::wcout << bold << L"  " << s << end_effect << std::endl << L"\n";
        }
    }
}

void printHelper(std::vector<std::wstring> helpers, const std::vector<int>& selections){
    std::wcout << L"\n" << std::endl;
    for (int selection : selections){
        std::wcout << italic << helpers[selection] << end_italic << std::endl;
    }
}

void printMaximizeWarning(){
    std::wstring maximize_string = L" PLease maximize your window for a better experience!";
    std::wcout << L"\n" << centerUp(maximize_string) << std::endl;
}

void printDirectory(const std::wstring& directory) {
    std::wcout << bold << L" --";
    for (wchar_t c : directory){
        std::wcout << L"-";
    }
    std::wcout << L"\n| " << directory << L" |" << std::endl;
    std::wcout << L" --";
    for (wchar_t c : directory){
        std::wcout << L"-";
    }
    std::wcout << end_effect << L"\n\n\n";
}

void printMonoinformation(const std::wstring& wstr){
    std::wstring wigly_underline;
    std::wcout << L"\n\n\n" << std::endl;
    std::wcout << centerUp(L"-> "  + wstr +  L" <-") << std::endl;
    for (wchar_t c : wstr){
        wigly_underline.push_back(L'~');
    }
    for (int i = 0; i < 6; i++){
        wigly_underline.push_back(L'~');
    }
    std::wcout << centerUp(red + wigly_underline + end_effect) << std::endl;
}

void printGlobalStatisticsFurthestPathsInformation(const std::vector<std::pair<std::pair<Airport, Airport>, int>>& info){
    std::wstring wigly_underline;
    std::wcout << L"\n\n\n" << std::endl;
    std::wstring topper = L"The trips with the greatest number of stops are :";
    std::wcout << bold << centerUp(topper) << end_effect << std::endl;
    for (wchar_t c : topper){
        wigly_underline.push_back(L'~');
    }

    std::wcout << L"     " << centerUp(red + wigly_underline + end_effect) << L"\n" << std::endl;

    for (const std::pair<std::pair<Airport, Airport>, int>& pair1 : info){
        std::wstring wstr = L"-> From the airport " + underline + pair1.first.first.getWcode();
        wstr.append(end_effect);
        wstr.append(L" (" + pair1.first.first.getWname() + L") to ");
        wstr.append(underline);
        wstr.append(pair1.first.second.getWcode());
        wstr.append(end_effect);
        wstr.append(L" (" + pair1.first.second.getWname());
        wstr.append(L");");
        std::wcout << centerUpAndLineUp(wstr, 40) << std::endl;
    }

    std::wcout << L"\n     " << centerUpAndLineUp(bold + L"Having " + underline + std::to_wstring(info[0].second)
                                                  + end_effect + bold + L" stops" + end_effect, 40) << std::endl;
}

void printTableAirportCode(const std::vector<std::wstring>& wstring_list, int page, int elements_per_page, unsigned long selected_in_page, bool table_mode){
    std::wcout << L"\n\n" << bold << L" -------------------------------------------------------------- " << end_effect << L"\n";
    int count = 0;
    int count_for_selected = 0;
    for (const std::wstring& wstr : wstring_list){
        if (count >= page * elements_per_page && count < page * elements_per_page + elements_per_page){
            if (count_for_selected == selected_in_page && table_mode){
                std::wcout << L"| " << bg_light_red << italic << underline << bold
                           << wstr << std::wstring(60 - wstr.size(), L' ') << end_italic << end_bg
                           << end_effect << L" |" << std::endl;
            }
            else{
                std::wcout << L"| " << wstr << std::wstring(60 - wstr.size(), L' ') << L" |" << std::endl;
            }
            count_for_selected ++;
        }
        count ++;
    }
    if (wstring_list.empty()){std::wcout << "|" << italic << L"  No results                                                  " << end_effect << "|" << std::endl;}
    std::wcout << L"|" << bold << L"--------------------------------------------------------------" << end_effect << L"|\n";
    std::wcout << L"|" << italic << L" <('p')                                                ('n')> " << end_italic << L"|" << std::endl;
    std::wcout << L"|" << std::wstring(60 - std::to_string(page + 1).size() - std::to_string(wstring_list.size()/elements_per_page + 1).size(), ' ')
               << bold << page + 1 << L"/" << wstring_list.size()/elements_per_page + 1 << end_effect << L" |" << std::endl;
    std::wcout << bold << L" -------------------------------------------------------------- " << end_effect << std::endl;
    std::wcout << italic << L"\n Total Number : " << end_italic << bold<< wstring_list.size() << end_effect << std::endl;
}

void printMiniTitle(const std::wstring& wstr){
    std::wcout << L"  " << underline << wstr << end_effect << L"\n\n" << std::endl;
}

void printAirlinesChosen(const std::vector<std::wstring>& airlines){
    int count = 0;
    std::wcout << L"      " << bold << underline << L"Airlines preferred List" << end_effect;
    std::wcout << L"\n" << bold << L" ----------------------------------------------------------------------------------------------------------------------------- " << end_effect << std::endl;
    for (const std::wstring& ws : airlines){
        if (count == 0){
            std::wcout << L"| " << ws << L", ";
        }
        else if (count == 24){
            std::wcout << ws << L" |" << std::endl;
        }
        else{
            std::wcout << ws << L", ";
        }
        count ++;
        if (count == 25){
            count = 0;
        }
    }
    if(airlines.empty()){
        std::wcout << L"|" << italic << L"   No picks yet                                                                                                              " << end_italic << L"|";
    }
    std::wcout << L"\n" << bold << L" ----------------------------------------------------------------------------------------------------------------------------- " << end_effect << std::endl;
}

void printPossiblePaths(const std::vector<std::vector<Airport>>& vva, const shared_ptr<Application>& app, const std::vector<wstring>& ca){
    std::wcout << L"\n";
    for (const auto& va : vva){
        std::wcout << L"  " << std::wstring(98, L'-') << std::endl;
        for (int idx = 0; idx < va.size() - 1; idx ++){
            int spaceCalc1 = 29 + va[idx].getWcode().size() + va[idx].getWname().size() +
                             va[idx].getWcity().size() + va[idx].getWcountry().size();
            int spaceCalc2 = 24 + va[idx + 1].getWcode().size() + va[idx + 1].getWname().size() +
                             va[idx + 1].getWcountry().size() + va[idx + 1].getWcity().size();
            int spaceCalc3 = 33;
            std::wcout << L" | Go from " << va[idx].getWcode() << L" (" << va[idx].getWname() << L") Airport, in " <<
                       va[idx].getWcity() << L", " << va[idx].getWcountry() << std::wstring(100 - spaceCalc1, L' ') << L"|" << L"\n | To " << va[idx + 1].getWcode() << L" (" << va[idx + 1].getWname() <<
                       L") Airport, in " << va[idx + 1].getWcity() << L", " << va[idx + 1].getWcountry() << std::wstring(100 - spaceCalc2, L' ') << L"|" << std::endl;
            std::wcout << L" | With the following Airlines : ";
            for (auto airline : app->airlinesAvailableForFlight(va[idx], va[idx + 1])){
                if (std::find(ca.begin(), ca.end(), std::wstring(airline.begin(), airline.end())) != ca.end()){
                    std::wcout << std::wstring(airline.begin(), airline.end()) << L" ";
                    spaceCalc3 += 4;
                }
            }
            std::wcout << std::wstring(100 - spaceCalc3, L' ') << L"|" << std::endl;
        }
        std::wcout << L"  " << std::wstring(98, L'-') << std::endl;
    }
    if (vva.empty()){
        std::wcout << L"\n\n  " << italic << L"No paths" << end_italic;
    }
}