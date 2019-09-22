% diffusion2d_sor.m
%
% this code solves the 2d diffusion equation
%
%  d (df/dx)/dx + d (df/dy)/dy + g(x,y) = 0
%
% subject to the periodic condition in x,
% the Dirichlet condition f = fa at y=0,
% and the Neumann condition df/dy=q at y = Ly;
%
% SOR method is used.

clear all
%close all

Lx = 2;
Ly = 1;
fa= 0.2;
q =0.0;

% parameters for g(x,y)
xc = Lx/2;
yc = Ly/4;
sigx = 0.1*Lx;
sigy = 0.1*Ly;
g0   = 10;

Nx = 64;
Ny = 64;

iter_max = 5000;
tol = 1e-6;

dx = Lx/Nx;
dy = Ly/Ny;

dxs= dx*dx;
dys= dy*dy;

x = (0:1:Nx)*dx;
x = x(:);
y = (0:1:Ny)*dy;
y = y(:);

% compute g(x)
g = zeros(Nx+1,Ny+1);
for j=1:Ny+1
for i=1:Nx+1
   tmp    = -(x(i)-xc)^2/sigx^2 - (y(j)-yc)^2/sigy^2; 
   g(i,j) = g0*exp(tmp);
end
end

% graph the function g(x,y)
% figure(1)
set(figure, 'Position', get(0, 'Screensize'))
surf(x, y, g')


% set up the initial guess for f(x,y)
f = zeros(Nx+2,Ny+2);    % we include the ghost node on the right and 
                         % on the top.
f(:,1) = fa;             % Dirichlet condition for j=1 (lower boundary)


%----------------------------------
% Successive Over Relaxation method
%----------------------------------
relax_sor = 1.5;     % if this is set to 1, you should get exactly the same
iter_save = zeros(1, iter_max+1);
error_save = zeros(1, iter_max+1);
% convergence as the Gauss-Seidel method.
iter=1;
error=1000;
while(iter <= iter_max & error > tol)
   % Note that each element of f is immediately in use after being updated.
   error = 0;
   for j=2:Ny+1
     for i=2:Nx+1
        fij_old = f(i,j);
       
        temp   = g(i,j)*dxs + (f(i-1,j)+f(i+1,j))           ...
                         + (f(i,j-1)+f(i,j+1))*dxs/dys; 
        f_temp = temp/(1 + dxs/dys)/2;  % difference between the intended
                                           % update and the current value.

        f(i,j) = f_temp*relax_sor + f(i,j)*(1 - relax_sor);     % actual update using a relaxation
                                           % factor.
        
        e_temp = abs(f(i,j) - fij_old);        
        if (error<e_temp) error=e_temp; end
     end
     % use the periodic boundary condition in x
     f(1,   j) = f(Nx+1,j);
     f(Nx+2,j) = f(2,   j);
   end
   % the Dirichlet B.C.
   f(:,1) = fa;
   % update the ghost node on the top according to the Neumann B.C.
   f(:,Ny+2) = f(:,Ny) + q * (2*dy);

   iter
   error
   error_save(iter) = error;
   iter_save(iter)  = iter;
   
   iter = iter+1;
end  % end while


% hold on
% loglog(iter_save, error_save)
% set(gca, 'fontsize', 20)
% xlabel('number of iterations, k', 'fontsize', 20)
% ylabel('|f^{k+1} - f^{k}|_{max}', 'fontsize', 20)
% grid on

% figure(3)
set(gca, 'fontsize', 18)
surf(x, y, f(1:Nx+1,1:Ny+1)'),
 xlabel('$$x$$', 'interpreter', 'latex')
 ylabel('$$y$$', 'interpreter', 'latex')
 zlabel('$$f(x,y)$$', 'interpreter', 'latex')
 title('$$\mathbf{Unsteady\ Steady-State\ Temperature\ Distribution\ f(x,y)\  N_{x} = 64\ and\ N_{y} = 64}$$', 'interpreter', 'latex')
set(gca, 'fontsize', 18)
 print('64UnsteadyTemperature', '-dpng')
shading interp


% save the results for other purposes
% save sor_results.mat x y f error_save iter_save;

