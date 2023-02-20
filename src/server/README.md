# IRC Server

### What is a Socket?
> A socket is a way to speak to other programs using standard Unix file descriptors.

#### Used system calls:

<details><summary>socket()</summary>
<p>


```int  socket(int domain, int type, int protocol);```

* `socket()` returns upon success a socket descriptor,  and -1  upon failure.

* `domain` Specifies the address family (protocol family) for the socket. In our case, we're gonna use **AF_INET**.

  * `AF_INET` is a constant that represents the address family (protocol family) used by the socket. It is an integer value to specify that the socket will use the IPv4 Internet protocols.

* `type` Specifies the type of communication semantics that will be used on the socket. In our case we're gonna use **SOCK_STREAM**.

  * `SOCK_STREAM` is a constant that represents the type of communication semantics that will be used on the socket. It is an integer value to specify that the socket will use a reliable, sequenced, and full-duplex connection-based data transmission service..

* `protocol` Specifies the specific protocol to be used with the socket. In our case we're gonna use **IPPROTO_TCP**.
  * `IPPROTO_TCP` is a constant that represents the protocol number for the Transmission Control Protocol (TCP) that will be used by the socket. It is an integer value that specifies that the socket will use the TCP protocol. The **IPPROTO_TCP** constant is typically used with the AF_INET address family and the SOCK_STREAM socket type to create a TCP socket.


</p>
</details>


<details><summary>setsockopt()</summary>
<p>

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
