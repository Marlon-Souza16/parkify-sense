from fastapi import FastAPI, Form
from fastapi.responses import HTMLResponse
import uvicorn

app = FastAPI()

dados_recebidos = []

@app.post("/dados")
async def receber_dados(dado: str = Form(...)):
    dado_limpo = dado.strip().replace('\r', '')
    partes = dado_limpo.split(" | ")

    leitura = {}

    for parte in partes:
        try:
            chave, valor = parte.split(": ", 1)
            leitura[chave.strip()] = valor.strip()
        except ValueError:
            print(f"Erro ao processar a parte: {parte}")
            leitura["Erro"] = parte

    dados_recebidos.append(leitura)

    print(f"Dado recebido: {leitura}")
    return {"message": "Dados recebidos com sucesso"}

@app.get("/dados")
async def visualizar_dados():
    dados_formatados = ""
    for dado in dados_recebidos:
        dado_str = "<br>".join([f"{chave}: {valor}" for chave, valor in dado.items()])
        dados_formatados += dado_str + "<br><br>"

    return HTMLResponse(content=f"<html><body>{dados_formatados}</body></html>")

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)
