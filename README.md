# rclc

A lightweight ROS 2 Client Library for the C language.

Currently, this repository contains one package only:

* [rclc](rclc/) provides all types and functions of the client library.

Technical information on the types and functions and use of this package is given in the README.md file in the corresponding subfolder.


## Requirements, how to build, test, install, use, etc.

Clone the repository into a ROS workspace and build it using [colcon](https://colcon.readthedocs.io/).


## License

rclc is open-sourced under the Apache-2.0 license. See the [LICENSE](LICENSE) file for details.

For a list of other open source components included in rclc, see the file [3rd-party-licenses.txt](3rd-party-licenses.txt).


## Known issues/limitations

Please notice the following issues/limitations:

*   rclc only provides basic subscriptions and publisher mechanisms. Currently, there is no support for timers, services, and other ROS 2 API concepts as known from rclcpp or rclpy.
