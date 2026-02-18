file(REMOVE_RECURSE
  "../../lib/libwallet.a"
  "../../lib/libwallet.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/wallet.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
