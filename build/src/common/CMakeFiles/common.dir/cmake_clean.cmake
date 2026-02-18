file(REMOVE_RECURSE
  "libcommon.a"
  "libcommon.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/common.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
