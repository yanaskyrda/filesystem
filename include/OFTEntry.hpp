#pragma once

#include <vector>

#include "Disk.hpp"
#include "Entities.hpp"
#include "IOSystem.hpp"

namespace FS {

class OFTEntry
{
public:
    OFTEntry(Entity::FileDescriptor file_descriptor, size_t descriptor_index, IOSystem* iosystem)
        : file_descriptor(file_descriptor)
        , descriptor_index(descriptor_index)
        , iosystem(iosystem)
    {
        cur_block = file_descriptor.indexes[0];
        changed_block = cur_block;
    }
    size_t writeToBuffer(const char* mem_area, size_t count);
    const char* readFromBuffer(size_t count);
    void setPosition(size_t new_pos);
    void onClose();
    bool isEmpty() const;
    size_t getDescriptorIndex() const;
    Entity::FileDescriptor getDescriptor();

private:
    char buffer[Disk::BLOCK_SIZE];
    size_t cur_pos = 0;
    size_t descriptor_index;
    Entity::FileDescriptor file_descriptor;
    size_t changed_block;
    size_t cur_block;
    IOSystem* iosystem;
    bool is_buffer_changed = false;
    void updateBuffer();
    size_t getCurrBlockIndex();
    size_t getNextBlock();
    bool moveToNextBlock(bool load_prev_to_disk);
    size_t getLengthByCurPos();
};

} // namespace FS