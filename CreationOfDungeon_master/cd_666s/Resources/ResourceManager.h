#ifndef RESOURCE_MGR
#define RESOURCE_MGR

#include <memory>
#include <map>
#include <vector>
#include "../Utility/Singleton.h"
#include "Resource.h"

/*
 ��������郊�\�[�X�n���h����
 ��ӂȃt�@�C���� �� shared_ptr�̃C���f�N�X�̃y�A �ŊǗ�����N���X
 */

class ResourceManager : public Singleton<ResourceManager>
{
    friend class Singleton<ResourceManager>;
    
public:
    
    //���\�[�X���쐬�E�擾
    std::shared_ptr<Resource> Create(std::shared_ptr<Resource> resource);
    
    //���\�[�X�̎Q�ƃJ�E���^���`�F�b�N���ĕs�v�Ȃ��̂��Ǘ�����O��
    void Update();
    //���\�[�X���Ƃ̎Q�Ɛ���DrawFormatString�ŏo��
    void Debug();
    
    void Clear();
    
    //���X�g����empty��؂�l�߂�
    void Refresh();
    
    //���\�[�X�Q�̍ŏ�ʃt�H���_�����擾
    std::string GetFolderPath() const { return _filePath; }
    void SetFolderPath(std::string str){ _filePath = str; }
    
    //���\�[�X��weak_ptr���擾
    std::weak_ptr<Resource> GetResource(std::string name);
    
    
private:
    
    //���\�[�X���Ǘ�����O���č폜
    void Remove(const std::string name);
    void Push(std::string name);
    
    ResourceManager();
    ~ResourceManager();
    
    //���\�[�X�f�B���N�g���̍ŏ�ʃp�X
    std::string _filePath;
    
    //�폜���ꂽ���\�[�X�̈ʒu�ɑ�����Ă������߂̋�̃��\�[�X
    const std::shared_ptr<Resource> _empty;
    
    //���\�[�X�̔z��
    std::vector< std::shared_ptr<Resource> > _resourceTable;
    
    //���\�[�X�̊Ǘ����̔z��
    std::map<std::string, size_t> _nameMap;
};

#define RESOURCE_TABLE ResourceManager::GetInstance()

#endif