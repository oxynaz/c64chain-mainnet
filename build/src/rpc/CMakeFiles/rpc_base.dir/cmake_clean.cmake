file(REMOVE_RECURSE
  "librpc_base.a"
  "librpc_base.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/rpc_base.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
