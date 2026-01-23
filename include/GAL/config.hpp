//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_CONFIG_HPP
#define GAL_CONFIG_HPP

#if __cplusplus >= 201703L
#define GAL_NODISCARD [[nodiscard]]
#define GAL_CONSTEXPR constexpr
#else
#define GAL_NODISCARD
#define GAL_MAYBE_UNUSED
#define GAL_CONSTEXPR
#endif

#endif //GAL_CONFIG_HPP
