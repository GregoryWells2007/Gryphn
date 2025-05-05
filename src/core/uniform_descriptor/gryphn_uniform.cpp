#include "gryphn_uniform.h"

void gnUniformSetCount(gnUniform& uniform, gnUInt count) {
    uniform.descriptorCount = count;
}
void gnUniformSetLayout(gnUniform& uniform, gnUniformLayout* uniformLayout) {
    uniform.uniformLayout = uniformLayout;
}
