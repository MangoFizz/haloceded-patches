// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

using namespace std;

struct Patch {
    vector<uint32_t> offsets;
    vector<uint8_t> bytes;
};

int main(int argc, const char **argv) {
    if(argc == 1) {
        cout << "Usage: haloceded-patch <path-to-haloceded.exe>" << endl;
        return 0;
    }

    filesystem::path file = argv[1];
    if(!filesystem::exists(file)) {
        cout << "Error: File does not exists!" << endl;
        return 1;
    }

    fstream haloceded;
    haloceded.open(file, ios::in | ios::out | ios::binary);

    /** Bump map file size limit to 1024 MiB */
    const Patch map_size = {{0x00042F22, 0x000436AD, 0x00044027, 0x0004474C}, {0x00, 0x00, 0x00, 0x40}};

    /** Bump tag data space to 64 MiB */
    const Patch tag_space = {{0x00044F02}, {0x00, 0x00, 0x44, 0x04}};
    
    auto apply_patch = [&haloceded](Patch patch) {
        for(auto offset : patch.offsets) {
            haloceded.seekp(offset, ios_base::beg);
            haloceded.write(reinterpret_cast<char *>(patch.bytes.data()), patch.bytes.size());
            haloceded.flush();
        }
    };

    apply_patch(map_size);
    apply_patch(tag_space);

    haloceded.close();

    cout << "Done: patches were applied successfully!" << endl;
    
    return 0;
}
