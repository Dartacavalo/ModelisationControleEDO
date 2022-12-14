## Projet en C++ | Réalisation d'un moteur de résolution d'EDO et illustration de la théorie du contrôle linéaire

L'accent est mis sur la programmation orientée objet, avec une abstraction faite sur la manière dont les objets sont structurés : problèmes de Cauchy, solveurs, méthodes de résolution.

Les fonctions représentées de la classe Controle, valables pour le contrôle en temps fini non-autonôme de l'équation en 1D : $x'(t) \ = \ A(t) x(t) \ + \ B(t) u(t)$

$$
\begin{align*}
        \begin{cases}
            u(t)& = B(t) \ \mathcal{R}(t_1, s)y \\
            y& = \mathbb{C}^{-1} (x_1 - \mathcal{R}(t_1, t_0))x_0 \\
            \mathbb{C}& = \int_{t_0}^{t_1} (\mathcal{R}(t_1, s)B(s))^2 ds \\
            \mathcal{R}(t, s)& = e^{\int_{s}^{t}A(t) dt}
        \end{cases}  \ \ \  
\end{align*}
$$

La solution exacte de ce problème est donnée par :

$$ x(t) = \mathcal{R}(t, t_0) x_0 + \int_{t_0}^{t} \mathcal{R}(t,s)B(s) u(s) ds $$

Les sorties graphiques utilisent gnuplot, c'est un logiciel libre disponible sur les dépôts Debian et Ubuntu.

Etant donné que les gestionnaires graphiques sont passés de X11/xorg à wayland sur les nouvelles versions de linux, il faut peut-être exécuter la commande :
```sh
export XDG_SESSION_TYPE=gnome-xorg
```
ou un équivalent pour un gestionnaire de bureau autre que gnome pour faire disparaitre les warnings de gnuplot.
