#include <CL/sycl.hpp>
#include <iostream>

using namespace sycl;
using std::cout;
using std::endl;

constexpr auto R = "\033[31m";
constexpr auto G = "\033[32m";
constexpr auto Y = "\033[33m";
constexpr auto B = "\033[34m";
constexpr auto GRAY = "\033[37m";
constexpr auto BOLD = "\033[1m";
constexpr auto NC = "\033[0m";

// class selector_enumerator : public device_selector

template <auto query, typename T>
void do_query(const T& obj_to_query, const std::string& name, int indent = 4) {
  cout << std::string(indent, ' ') << name << " is '"
       << obj_to_query.template get_info<query>() << "'\n";
}

int main(void) {
  //     for (auto const & this_platform : platform::get_platforms() ) {
  //         cout << "Found platform:\n";
  //         cout << "    name: " << get_info<info::platform::name>()
  //     }
  // }

  // Loop through the available platforms
  for (auto const& platform : platform::get_platforms()) {
    cout << "\n";
    cout << BOLD << "Platform " << NC
         << platform.get_info<info::platform::name>() << "\n";
    cout << GRAY << "    ver. " << NC
         << platform.get_info<info::platform::version>() << "\n";
    cout << GRAY << "   vend. " << NC
         << platform.get_info<info::platform::vendor>() << "\n";

    // Loop through the devices available in this plaform
    cout << GRAY << " Devices:\n" << NC;
    for (auto& device : platform.get_devices()) {
      cout << "         " << BOLD << device.get_info<info::device::name>() << NC
           << "\n";
      cout << GRAY << "                          Type " << NC
           << (device.is_host()
                   ? "Host"
                   : (device.is_cpu() ? "CPU"
                                      : (device.is_accelerator() ? "Accelerator"
                                                                 : "Unknown")))
           << "\n";
      cout << GRAY << "                        Vendor " << NC
           << device.get_info<info::device::vendor>() << "\n";
      cout << GRAY << "                        Driver " << NC
           << device.get_info<info::device::driver_version>() << "\n";
      // do_query<info::device::vendor>(device, "info::device::vendor");
      cout << GRAY << "    Max. work item dimensions: " << NC
           << device.get_info<info::device::max_work_item_dimensions>() << "\n";
      cout << GRAY << "          Max work group size: " << NC
           << device.get_info<info::device::max_work_group_size>() << "\n";
      cout << GRAY << "        Base memory alignment: " << NC
           << device.get_info<info::device::mem_base_addr_align>() << "\n";
      cout << GRAY << "    partition_max_sub_devices: " << NC
           << device.get_info<info::device::partition_max_sub_devices>()
           << "\n";
    }
  }
  cout << "\n";
}