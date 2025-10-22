cat > README.md <<EOF
# Sistema de Controle de Pedidos (SCP)

Projeto da disciplina **Práticas de Programação** – UEG  
Desenvolvido em **C** com interface **ncurses** e persistência em **CSV**.

## Como compilar (no WSL/Ubuntu)

\`\`\`bash
sudo apt install build-essential libncurses5-dev libncursesw5-dev
make
make run
\`\`\`

## Estrutura
- \`src/\`: código-fonte
- \`include/\`: cabeçalhos
- \`data/\`: arquivos CSV
- \`build/\`: executável e objetos
EOF