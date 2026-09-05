# networking all-in-one for dummies, 9th edition

use this alongside linux study. start with books 1 and 2, then read the minibook for the task you want to practise. the author treats it as a reference, so you don't need to read all 10 minibooks in order.

```sh
nvim .
mise run setup                       # first installation only
mise run shell                       # enter the client
mise run shell -- server             # enter the server
mise run run -- client ping -c 1 server
mise run verify
mise run stop                        # stop both machines
```

the fedora lab has 2 containers for practising ip, dns, http, and packet inspection. their network has no external route or published ports. save scripts in `exercises/` and packet captures in `.state/`.

this lab covers basic network commands. full server administration needs a vm. the [book](https://www.dummies.com/book/general-networking-33585/networking-all-in-one-for-dummies-281780/) also covers windows server 2025, windows clients, fedora server, vmware, hyper-v, cloud accounts, and network hardware.

those sections need the matching os or equipment. [windows server evaluation](https://www.microsoft.com/en-us/evalcenter/evaluate-windows-server-2025) requires registration and expires after 180 days; install it when you reach that material. [fedora server](https://fedoraproject.org/server/download/) is free. this setup hasn't provisioned cloud accounts, windows installations, or physical networking.

follow the book's procedures as practice. it has no single companion code repository or separate programming exercise set.
