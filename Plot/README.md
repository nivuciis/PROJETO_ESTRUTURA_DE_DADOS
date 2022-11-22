[![Typing SVG](https://readme-typing-svg.herokuapp.com?font=Ubuntu&size=20&color=0000FF&center=true&lines=HEAP+VS+PRIORITY+QUEUE)](https://git.io/typing-svg)
<h2>Resumo</h2>
<p>A contagem de iterações é realizada utilizando uma variavel do tipo double global que adiciona ajustando valores a cada iteração realizada pelas funções das duas estruturas. Após a contagem ser feita os valores são adicionados em arquivos de texto para serem utilizados para a plotagem.</p>
<p>Na plotagem são feitas duas listas para cada estrutura representando os valores de cada iteração das funções de enqueue e dequeue das estruturas, em seguida é realizado o plot utilizando a biblioteca do matplotlib.</p>
<p>No gráfico da função enqueue() é notável um leve erro para a estrutura de fila de prioridade, iniciando com um comportamento de O(n) e em seguida aumenta para O(n^2)</p>
<img src="Figure_1.png" alt="Enqueue">
<img src="Figure_2.png" alt="Dequeue">
