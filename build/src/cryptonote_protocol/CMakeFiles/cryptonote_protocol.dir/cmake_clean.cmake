file(REMOVE_RECURSE
  "libcryptonote_protocol.a"
  "libcryptonote_protocol.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/cryptonote_protocol.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
