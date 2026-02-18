file(REMOVE_RECURSE
  "libdaemon_rpc_server.a"
  "libdaemon_rpc_server.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/daemon_rpc_server.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
