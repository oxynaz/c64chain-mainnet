file(REMOVE_RECURSE
  "libdevice.a"
  "libdevice.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/device.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
