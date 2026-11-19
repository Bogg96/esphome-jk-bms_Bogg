#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace esphome {
namespace jk_rs485_sniffer {

// ESPHome removed the std::string format_hex_pretty() helper (2026.x); its
// replacement, format_hex_pretty_to(), writes into a caller-supplied buffer.
// This small helper keeps the old log look ("02.10.00.04.00.02.04 (13)") and
// does not depend on any ESPHome API, so it builds on old and new releases.
inline std::string hex_pretty(const uint8_t *data, size_t len, char separator = '.', bool show_length = true) {
  static const char kHex[] = "0123456789ABCDEF";
  std::string out;
  out.reserve(len * 3 + 8);
  for (size_t i = 0; i < len; i++) {
    if (i > 0) {
      out.push_back(separator);
    }
    out.push_back(kHex[data[i] >> 4]);
    out.push_back(kHex[data[i] & 0x0F]);
  }
  if (show_length && len > 4) {
    out += " (";
    out += std::to_string(len);
    out += ")";
  }
  return out;
}

}  // namespace jk_rs485_sniffer
}  // namespace esphome
