#include "gryphn_buffer.h"

void gnBufferSetSize(gnBuffer& buffer, gnSize size) {
    buffer.size = size;
}
void gnBufferSetType(gnBuffer& buffer, gnBufferType type) {
    buffer.bufferType = type;
}
void gnBufferSetDataType(gnBuffer& buffer, gnBufferDataType type) {
    buffer.dataType = type;
}
