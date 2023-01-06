## Projet en C++ | Réalisation d'un moteur de résolution d'EDO et illustration de la théorie du contrôle linéaire

L'accent est mis sur la programmation orientée objet, avec une abstraction faite sur la manière dont les objets sont structurés : problèmes de Cauchy, solveurs, méthodes de résolution.

Les fonctions de la classe Controle, valables pour le contrôle non-autonôme de l'équation en 1D : $x'(t) \ = \ A(t) x(t) \ + \ B(t) u(t)$

$$
\begin{align*}
        \left\{
        \begin{array}{llll}
            u(t)& = B(t) \ \mathcal{R}(t_1, s)y \\
            y& = \mathbb{C}^{-1} (x_1 - \mathcal{R}(t_1, t_0))x_0\\
            \mathbb{C}& = \int_{t_0}^{t_1} (\mathcal{R}(t_1, s)B(s))^2 ds\\
            \mathcal{R}(t, s)& = x_0 e^{\int_{t_0}^{t_1}A(t) dt}
        \end{array}  \ \ \  
    \right. 
\end{align*}
$$
