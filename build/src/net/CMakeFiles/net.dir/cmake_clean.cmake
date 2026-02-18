file(REMOVE_RECURSE
  "libnet.a"
  "libnet.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/net.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
