/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   about_png;
    const int            about_pngSize = 36971;

    extern const char*   add_png;
    const int            add_pngSize = 16103;

    extern const char*   default_chalayout;
    const int            default_chalayoutSize = 3662;

    extern const char*   icon_png;
    const int            icon_pngSize = 42153;

    extern const char*   in_png;
    const int            in_pngSize = 3358;

    extern const char*   nextcue_png;
    const int            nextcue_pngSize = 16077;

    extern const char*   out_png;
    const int            out_pngSize = 3368;

    extern const char*   playpause_png;
    const int            playpause_pngSize = 16163;

    extern const char*   prevcue_png;
    const int            prevcue_pngSize = 16089;

    extern const char*   snap_png;
    const int            snap_pngSize = 3649;

    extern const char*   stop_png;
    const int            stop_pngSize = 15967;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 11;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
