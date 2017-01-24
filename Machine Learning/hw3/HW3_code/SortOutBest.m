function [B_percepwithmar_eta,B_winnow_alpha,B_winnowwithmar_alpha,B_winnowwithmar_gamma,B_adagrad_eta]=...
SortOutBest(test_percepwithmar,percepwithmar_eta,test_winnow,winnow_alpha,test_winnowwithmar,...
winnowwithmar_alpha,winnowwithmar_gamma,test_adagrad,adagrad_eta)

[value,coords]=min(test_percepwithmar);
B_percepwithmar_eta=percepwithmar_eta(coords,1);
disp('Best case in Percep With Margin has error : ');disp(value);

[value,coords]=min(test_winnow);
B_winnow_alpha=winnow_alpha(coords,1);
disp('Best case in Winnow Basic has error : ');disp(value);

value=10^10;
alpha_posi=0;
gamma_posi=0;
for i=1:size(test_winnowwithmar,1)  % note alpha is the row
    for j=1:size(test_winnowwithmar,2)
        if test_winnowwithmar(i,j)<value
            value=test_winnowwithmar(i,j);
            alpha_posi=i;           % note alpha is the row
            gamma_posi=j;
        end
    end
end
B_winnowwithmar_alpha=winnowwithmar_alpha(alpha_posi,1);
B_winnowwithmar_gamma=winnowwithmar_gamma(gamma_posi,1);
disp('Best case in Winnow With Margin has error : ');disp(value);

[value,coords]=min(test_adagrad);
B_adagrad_eta=adagrad_eta(coords,1);
disp('Best case in Ada Grad has error : ');disp(value);