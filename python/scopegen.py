import datalink as dl



resource_manager = dl.rm()

fun_generator= dl.findgen(resource_manager, 1)
scope_handle = dl.findscope(resource_manager,1)

dl.setSinWave(fun_generator,1,10,200,0,0)
