file(REMOVE_RECURSE
  "librpc.a"
  "librpc.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/rpc.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
