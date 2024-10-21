# SUGER リファレンス  
## 使い方  
- **シーンの作成**  
  - **ヘッダファイル**  
  BaseScene.hをインクルード、BaseSceneClassを継承してください。  
  void Initialize();  
  void Finalize();  
  void Update();  
  をオーバーライドしてください。  
  SampleScene.hを参考にするとわかりやすいです。  

  - **ソースファイル**  
  Initialize関数の先頭に、BaseScene::Initialize();  
  Update関数の末尾に、BaseScene::Update();  
  を追加してください。  
  SampleScene.cppを参考にするとわかりやすいです。  

- **オブジェクトの作成**
