<?hh //strict

namespace bookman\reader;

use \SplFileObject;


final class File
{

    private ?SplFileObject $file;
    private bool $opended = false;

    public function __construct(string $filePath)
    {
        $this->file = new SplFileObject($filePath, 'r');
        $this->file->setFlags(SplFileObject::DROP_NEW_LINE);
        $this->opended = true;
    }

    public function getName() : string
    {
        return $this->file->getFilename();
    }

    public function getPath() : string
    {
        return $this->file->getPathname();
    }

    public static function fromString(string $filePath) : File
    {
        return new self($filePath);
    }

    public function readBytes(int $length) : ReadedChunk
    {
        $content = $this->file->fread($length);
        return new ReadedChunk($content);
    }

    public function readRecord() : ReadedRecord
    {
        $content = $this->file->fgets();
        return new ReadedRecord($content);
    }

    public function exists() : bool
    {
        return file_exists($this->getPath());
    }

    public function close() : void
    {
        $this->file = null;
        $this->opended = false;
    }

    public function __destruct() : void
    {
        if ($this->opended === false) {
            return;
        }
        $this->close();
    }

}
