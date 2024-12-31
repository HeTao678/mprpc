#aux_source_directory(. SRC_LIST)
#因为我们刚才proto生成了.cc文件，当前CMakeLists.txt识别不了。如果不修改成现在的样式，我们得到终端命令行的build里面，把文件全部删除，然后执行cmake ..
set(SRC_LIST 
    mprpcapplication.cc 
    mprpcconfig.cc 
    rpcheader.pb.cc 
    mprpcprovider.cc 
    mprpcchannel.cc
    mprpccontroller.cc 
    logger.cc
    zookeeperutil.cc
)
add_library(mprpc ${SRC_LIST})
target_link_libraries(mprpc muduo_net muduo_base pthread  zookeeper_mt)

