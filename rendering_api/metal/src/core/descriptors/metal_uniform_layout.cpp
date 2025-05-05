#include <core/uniform_descriptor/gryphn_uniform_layout.h>

struct gnPlatformUniformLayout {

};

GN_EXPORT gnReturnCode gnCreateUniformLayoutFn(gnUniformLayout* uniformLayout, gnOutputDevice& device) {
    if (uniformLayout->uniformLayout == nullptr) uniformLayout->uniformLayout = new gnPlatformUniformLayout();
    return GN_SUCCESS;
}
GN_EXPORT void gnDestroyUniformLayoutFn(gnUniformLayout& uniformLayout) {

}
