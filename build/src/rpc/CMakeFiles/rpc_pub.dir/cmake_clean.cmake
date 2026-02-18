file(REMOVE_RECURSE
  "librpc_pub.a"
  "librpc_pub.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/rpc_pub.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
