# Data Flow

Two data storage are used in OpenGL.

* Buffer
* Texture

## Vertex Array Buffer(VAO)

A VAO is needed

```plantuml
CPU -> OpenGL:glCreateVertexArrays
OpenGL -> CPU:OK
CPU -> OpenGL:glBindVertexArray
OpenGL -> CPU:OK
```

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

You can put all attributes to one vertex buffer or put one attribute to one buffer.

```plantuml
== attribute <--> binding index==
CPU -> OpenGL:glVertexArrayAttribBinding
OpenGL -> CPU:OK
== binding index <--> Buffer==
CPU -> OpenGL:glVertexArrayVertexBuffer
OpenGL -> CPU:OK
== Set vertex attribute format==
CPU -> OpenGL:glVertexArrayAttribFormat
OpenGL -> CPU:OK
== Enable vertex attribute==
CPU -> OpenGL:glEnableVertexAttribArray
OpenGL -> CPU:OK
```

### get data to uniform from buffer
