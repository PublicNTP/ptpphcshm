# ptpphcshm

Relay high-precision time data from the PTP PHC device to a shared memory (SHM) segment that NTPd and friends can read.


# Prereqs

* Download linuxptp-2.0 from https://sourceforge.net/projects/linuxptp/files/v2.0/linuxptp-2.0.tgz/download
* tar zxvfp linuxptp-2.0
* cd linuxptp-2.0
* make
* sudo make install



# Legal

This project is copyrighted by PublicNTP, Inc., then open-sourced for the public good under the MIT License.


# Thanks

Jacob Keller <jacob.keller@gmail.com> for his awesome work on `linuxptp`.
