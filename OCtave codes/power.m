% run the experiment 10 times, showing the results of each iteration for 1 second
for iterations=1:10
alpha=1.7;
nr = unique(round(logspace(1,6,40))); % sizes of samples to simulate
mn = zeros(length(nr),1); % storage for sample means
vr = zeros(length(nr),1); % storage for sample variances
for i=1:length(nr)
n = nr(i); % set the size of the iid sample
for j=1:size(mn,2)
x = randht(n,’powerlaw’,alpha); % generate iid PL r.v.
mn(i,j) = mean(x); % compute the sample mean
vr(i,j) = var(x); % compute the sample variance
end;
end;
% make a pretty figure
figure(2);
loglog(nr,mn,’ro’,’LineWidth’,2,’MarkerFaceColor’,[1 1 1]); hold on;
loglog(nr,vr,’bo’,’LineWidth’,2,’MarkerFaceColor’,[1 1 1]); hold off;
set(gca,’FontSize’,fs,’XLim’,10.^[1 6],’YLim’,10.^[0 9]);
set(gca,’XTick’,10.^(1:6),’YTick’,10.^(0:9));
xlabel(’Size of sample, n’,’FontSize’,16);
ylabel(’Value’,’FontSize’,16);
h=legend(’Sample mean’,’Sample variance’,2); set(h,’FontSize’,16);
h=text(8*10^4,10^8,strcat(’\alpha=’,num2str(alpha,’%3.1f’))); set(h,’FontSize’,16);
drawnow; % force Matlab to draw the figure now (flush the graphics queue)
pause(1); % pause for 1 second before continuing the loop
end;