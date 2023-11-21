

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
<h3 align="center">Project to challenge the skills I learned recently :)</h3>
  <p align="center">
    <br />
    <a href="https://github.com/Ysadsir/yotflix"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Ysadsir/yotflix">View Demo</a>
    ·
    <a href="https://github.com/Ysadsir/yotflix/issues">Report Bug</a>
    ·
    <a href="https://github.com/Ysadsir/yotflix/issues">Request Feature</a>
  </p>
</div>


<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://cv.ygherve.online/resume.html)

Deployments for jellyfin, deluge and jackett in my own k3s cluster made with 3 Raspberry Pi. A fourth pi with Ubuntu and a 1 To HDD for monitoring (Prometheus and grafana).

### Built With

* [![K3s][K3s]][K3s-url]
* [![Docker][Docker]][Docker-url]
* [![Ansible][Ansible]][Ansible-url]
* [![Raspberrypi][Raspberrypi]][Raspberrypi-url]
* [![Jellyfin][Jellyfin]][Jellyfin-url]
* [![Prometheus][Prometheus]][Prometheus-url]
* [![Grafana][Grafana]][Grafana-url]
* [![Arduino][Arduino]][Arduino-url]
  
<!-- GETTING STARTED -->
## Getting Started

### Prerequisites


* git
  ```sh
  sudo apt install git-all
  ```
* k3s
  ```sh
  sudo k3s server &
  # Kubeconfig is written to /etc/rancher/k3s/k3s.yaml
  sudo k3s kubectl get node

  # On a different node run the below command. 
  # NODE_TOKEN comes from /var/lib/rancher/k3s/server/node-token on your server
  sudo k3s agent --server https://myserver:6443 --token ${NODE_TOKEN}
  ```

### Installation

* Clone the repo
   ```sh
   git clone https://github.com/Ysadsir/yotflix.git
   ```




<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


<!-- LICENSE -->
## License

Distributed under The Unlicense License. See `LICENSE` for more information.


<!-- CONTACT -->
## Contact

Project Link: [https://github.com/Ysadsir/yotflix](https://github.com/Ysadsir/yotflix)





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/Ysadsir/yotflix.svg?style=for-the-badge
[contributors-url]: https://github.com/Ysadsir/yotflix/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Ysadsir/yotflix.svg?style=for-the-badge
[forks-url]: https://github.com/Ysadsir/yotflix/network/members
[stars-shield]: https://img.shields.io/github/stars/Ysadsir/yotflix.svg?style=for-the-badge
[stars-url]: https://github.com/Ysadsir/yotflix/stargazers
[issues-shield]: https://img.shields.io/github/issues/Ysadsir/yotflix.svg?style=for-the-badge
[issues-url]: https://github.com/Ysadsir/yotflix/issues
[license-shield]: https://img.shields.io/github/license/Ysadsir/yotflix.svg?style=for-the-badge
[license-url]: https://github.com/Ysadsir/yotflix/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/yves-guillaume-herve
[product-screenshot]: images/screenshot.png

[K3s]: https://img.shields.io/badge/k3s-FFFFFF?style=for-the-badge&logo=k3s&logoColor=FFC61C
[K3s-url]: https://k3s.io/
[Docker]: https://img.shields.io/badge/docker-FFFFFF?style=for-the-badge&logo=docker&logoColor=2496ED
[Docker-url]: https://www.docker.com/
[Ansible]: https://img.shields.io/badge/ansible-EE0000?style=for-the-badge&logo=ansible&logoColor=FFFFFF
[Ansible-url]: https://www.ansible.com/
[Raspberrypi]: https://img.shields.io/badge/raspberrypi-FFFFFF?style=for-the-badge&logo=raspberrypi&logoColor=A22846
[Raspberrypi-url]: https://www.raspberrypi.com/
[Jellyfin]: https://img.shields.io/badge/jellyfin-000000?style=for-the-badge&logo=jellyfin&logoColor=00A4DC
[Jellyfin-url]: https://jellyfin.org/
[Prometheus]: https://img.shields.io/badge/prometheus-E6522C?style=for-the-badge&logo=prometheus&logoColor=FFFFFF
[Prometheus-url]: https://prometheus.io/
[Grafana]: https://img.shields.io/badge/grafana-000000?style=for-the-badge&logo=grafana&logoColor=F46800
[Grafana-url]: https://grafana.com/
[Arduino]: https://img.shields.io/badge/arduino-FFFFFF?style=for-the-badge&logo=arduino&logoColor=00878F
[Arduino-url]: https://www.arduino.cc/
