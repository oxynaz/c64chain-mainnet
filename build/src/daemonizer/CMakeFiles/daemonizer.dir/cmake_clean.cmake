file(REMOVE_RECURSE
  "libdaemonizer.a"
  "libdaemonizer.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/daemonizer.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
