file(REMOVE_RECURSE
  "libhardforks.a"
  "libhardforks.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/hardforks.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
