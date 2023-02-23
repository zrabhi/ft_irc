# IRC Server

### What is a Socket?
> A socket is a way to speak to other programs using standard Unix file descriptors.

#### Used system calls:

<details><summary>socket()</summary>
<p>

The `socket()` function is used to create a new communication endpoint, called a socket, that can be used for network communication.

```int  socket(int domain, int type, int protocol);```

* `socket()` returns upon success a socket descriptor,  and -1  upon failure.

* `domain` Specifies the address family (protocol family) for the socket. In our case, we're gonna use **AF_INET**.

  * <span style="color: green">`AF_INET` is a constant that represents the address family (protocol family) used by the socket. It is an integer value to specify that the socket will use the IPv4 Internet protocols.</span>

* `type` Specifies the type of communication semantics that will be used on the socket. In our case we're gonna use **SOCK_STREAM**.

  * <span style="color: green">`SOCK_STREAM` is a constant that represents the type of communication semantics that will be used on the socket. It is an integer value to specify that the socket will use a reliable, sequenced, and full-duplex connection-based data transmission service.</span>

* `protocol` Specifies the specific protocol to be used with the socket. In our case we're gonna use **IPPROTO_TCP**, or 0 which which defaults to *IPPROTO_TCP*.
  * <span style="color: green">`IPPROTO_TCP` is a constant that represents the protocol number for the Transmission Control Protocol (TCP) that will be used by the socket. It is an integer value that specifies that the socket will use the TCP protocol. The **IPPROTO_TCP** constant is typically used with the AF_INET address family and the SOCK_STREAM socket type to create a TCP socket.</span>


</p>
</details>


<details><summary>setsockopt()</summary>
<p>

The `setsockopt()` function is used to set options on a socket. It allows the program to specify various socket options, such as enabling/disabling certain features or setting the value of various parameters.

```setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);```

The function takes the following arguments:

* `socket`: The file descriptor of the socket on which to set the option.
  * <span style="color: green">Here we're gonna set options for the socket descriptor we got from `socket()`.</span>

* `level`: The protocol level at which the option resides. For example, SOL_SOCKET indicates that the option is at the socket API level.
  * <span style="color: green">`SOL_SOCKET` is short for "Socket Options Level - Socket". It's used to set socket options at the socket level.</span>

* `option_name`: The name of the option to set.
  * <span style="color: green">The `SO_REUSEADDR` option allows a socket to bind to a local address that is already in use by another socket. This is useful in situations where a server needs to restart or bind to the same address and port quickly after a connection is closed.</span>

* `option_value`: A pointer to the value to set for the option.

* `option_len`: The size in bytes of the option_value

</p>
</details>


<details><summary>bind()</summary>
<p>



</p>
</details>

<details><summary>listen()</summary>
<p>

</p>
</details>

<details><summary>connect()</summary>
<p>

</p>
</details>

<details><summary>accept()</summary>
<p>

</p>
</details>

<details><summary>send()</summary>
<p>

</p>
</details>

<details><summary>recv()</summary>
<p>

</p>
</details>
