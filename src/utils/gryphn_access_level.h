#pragma once

#ifdef GN_REVEAL_IMPL
#define ACCESS_LEVEL public
#else
#define ACCESS_LEVEL protected
#endif
