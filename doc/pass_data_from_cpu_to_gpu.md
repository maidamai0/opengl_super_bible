# Data Flow

Two data storage are used in OpenGL.

* Buffer
* Texture

## Buffer

## Get data to buffer

```plantuml
==Create a handle==
CPU -> OpenGL:glCreateBuffers
OpenGL -> GPU:reserve a name(buffer handle)
GPU -> OpenGL
OpenGL -> CPU

== Allocate memory on GPU==
note left OpenGL:Method 1, initialize GPU memory
CPU -> OpenGL:gl[Named]BufferStorage
OpenGL -> GPU:allocate memory(data store)
GPU -> OpenGL
OpenGL -> CPU:OK

== Pass data to GPU==
note left OpenGL:Method 2, directly copy data to GPU
CPU -> OpenGL:gl[Named]BufferSubData
OpenGL -> GPU:copy data
OpenGL -> CPU:OK

note left OpenGL:Method 3,Map GPU data pointer to CPU
CPU -> OpenGL:glMap[Named]Buffer[Range]
OpenGL -> GPU:get the pointer to the data store/memory
OpenGL -> CPU:data pointer
CPU -> CPU:copy data to the pointer
OpenGL -> CPU:OK

note left OpenGL:Method 4,fill with constant value
CPU -> OpenGL:glClear[Named]BufferSubData
OpenGL -> GPU:fill data store with constant value
OpenGL ->CPU:OK

== Bind and use buffer==
CPU -> OpenGL:glBindBuffer
OpenGL -> CPU:OK

== GPU to GPU==
CPU -> OpenGL:glCopy[Named]BufferSubData
OpenGL -> GPU:copy data from one buffer to another
OpenGL -> CPU:OK
```

### Get data to vertex attributes from buffer

### get data to uniform from buffer
